import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Set;
import java.util.HashSet;
import java.util.Scanner;
import java.util.concurrent.Executors;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.security.KeyManagementException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;
 
import javax.net.ssl.KeyManagerFactory;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLServerSocket;
import javax.net.ssl.SSLServerSocketFactory;
import javax.net.ssl.SSLSocket;

public class SSLServer {
	
	
	
    // All client names, so we can check for duplicates upon registration.
    private static Set<String> names = new HashSet<>();

    // The set of all the print writers for all the clients, used for broadcast.
    private static Set<PrintWriter> writers = new HashSet<>();

    public static void main(String[] args) throws Exception {
    final int port = 59001; // listening port
   	 String keyFile = "SSLkeys/myKeyStore.jks"; // key store file
   	 String keyFilePass = "1980pop"; // cryptographic key store
   	 String keyPass = "1980pop"; // key alias password
   	 SSLServerSocket sslsocket = null; // secure connection socket
   	 KeyStore ks; // key store
   	 KeyManagerFactory kmf; // key management facility
   	 SSLContext sslc = null; // secure connection
   	 // initialize a secure connection key
   	try {
   		ks = KeyStore.getInstance("JKS");
   		ks.load(new FileInputStream(keyFile), keyFilePass.toCharArray());
   		 // Create X.509 key manager manage JKS keystore
   		kmf = KeyManagerFactory.getInstance("SunX509");
   		kmf.init(ks, keyPass.toCharArray());
   		 // constructor SSL environment, specify the SSL version 3.0, you can also use TLSv1, SSLv3 but more common
   		sslc = SSLContext.getInstance("SSLv3");
   		 // initialize SSL environment. The second parameter is the source of trusted certificates tell JSSE to use,
   		 // set is to obtain a certificate from javax.net.ssl.trustStore as null. The third parameter is a random number generated JSSE,
   		 // This parameter will affect the security of the system, set to null is a good choice, can guarantee the security of JSSE.
   		sslc.init(kmf.getKeyManagers(), null, null);
   	} catch (KeyManagementException ex) {
   		
   	} catch (KeyStoreException e) {
   		
   		e.printStackTrace();
   	} catch (NoSuchAlgorithmException e) {
   
   		e.printStackTrace();
   	} catch (CertificateException e) {
   		
   		e.printStackTrace();
   	} catch (UnrecoverableKeyException e) {
   		
   		e.printStackTrace();
   	}
   	
   	 // secure connection with the factory to create a secure connection socket
   	SSLServerSocketFactory sslssf = sslc.getServerSocketFactory();
   	 sslsocket = (SSLServerSocket) sslssf.createServerSocket (); // Create and enter monitor
   	SocketAddress sa=new InetSocketAddress("localhost",port);
   	sslsocket.bind(sa);
   	System.out.println("Listening...");
   	System.out.println("The chat server is running...");
   	
   	//Multi-clients creation 
       var pool = Executors.newFixedThreadPool(500);
            while (true) {
            	SSLSocket ssocket = (SSLSocket) sslsocket.accept();
                pool.execute(new Handler(ssocket));
            }
       // }
    }
    
     // The client handler task.
     
    private static class Handler implements Runnable {
        private String name;
        private SSLSocket socket;
        private Scanner in;
        private PrintWriter out;

        /*
         * Constructs a handler thread, squirreling away the socket. All the interesting
         * work is done in the run method. Remember the constructor is called from the
         * server's main method, so this has to be as short as possible.
         */
        public Handler(SSLSocket socket) {
            this.socket = socket;
        }

        /*
         * Services this thread's client by repeatedly requesting a screen name until a
         * unique one has been submitted, then acknowledges the name and registers the
         * output stream for the client in a global set, then repeatedly gets inputs and
         * broadcasts them.
         */
        public void run() {
            try {
                in = new Scanner(socket.getInputStream());
                out = new PrintWriter(socket.getOutputStream(), true);

                // Keep requesting a name until we get a unique one.
                while (true) {
                    out.println("SUBMITNAME");
                    name = in.nextLine();
                    if (name == null) {
                        return;
                    }
                    synchronized (names) {
                        if (!name.isBlank() && !names.contains(name)) {
                            names.add(name);
                            break;
                        }
                    }
                }

                // Now that a successful name has been chosen, add the socket's print writer
                // to the set of all writers so this client can receive broadcast messages.
                // But BEFORE THAT, let everyone else know that the new person has joined!
                out.println("NAMEACCEPTED " + name);
                for (PrintWriter writer : writers) {
                    writer.println("MESSAGE " + name + " has joined");
                }
                writers.add(out);

                // Accept messages from this client and broadcast them.
                while (true) {
                    String input = in.nextLine();
                    if (input.toLowerCase().startsWith("exit")) {
                        return;
                    }
                    for (PrintWriter writer : writers) {
                        writer.println("MESSAGE " + name + ": " + input);
                    }
                }
            } catch (Exception e) {
                System.out.println(e);
            } finally {
                if (out != null) {
                    writers.remove(out);
                }
                if (name != null) {
                    System.out.println(name + " is leaving");
                    names.remove(name);
                    for (PrintWriter writer : writers) {
                        writer.println("MESSAGE " + name + " has left");
                    }
                }
                try {
                    socket.close();
                } catch (IOException e) {
                }
            }
        }
    }
}
