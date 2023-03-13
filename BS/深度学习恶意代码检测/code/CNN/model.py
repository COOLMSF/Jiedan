import os
from utils.utils import exec2img

#define a function for AlexNet model
class Alexnet():
    model = None
    
    def __init__(self):
        #define the model as sequential model
        model = Sequential()

        #layer 1 of the model  ------>  convolutional layer + max-pooling layer
        model.add(Conv2D(filters = 96, kernel_size = (11,11), strides= 4, padding = 'valid', 
                         activation='relu', input_shape=(img_size,img_size,3)))
        model.add(MaxPooling2D(pool_size = (3,3), strides = 2))

        #layer 2 of the model  ------>  convolutional layer + max-pooling layer
        model.add(Conv2D(filters = 256, kernel_size = (5,5), padding = 'same', 
                         activation = 'relu'))
        model.add(MaxPooling2D(pool_size = (3,3), strides = 2))

        #layers 3 to 5  of the model  ------>  convolutional layer + 1 max-pooling layer
        model.add(Conv2D(filters = 384, kernel_size = (3,3), padding = 'same', 
                         activation = 'relu'))
        model.add(Conv2D(filters = 384, kernel_size = (3,3), padding = 'same', 
                         activation = 'relu'))
        model.add(Conv2D(filters = 256, kernel_size = (3,3), padding = 'same', 
                         activation = 'relu'))
        model.add(MaxPooling2D(pool_size = (3,3), strides = 2))

        #layers 6 to 8 of the model  ------> two fully connected hidden layers and one fully connected output layer

        #make a flatten layer
        model.add(Flatten())
  
        #set the output layer activation as a softmax 
        model.add(Dense(25, activation = 'softmax'))

        #compile the model using adam optimizer
        model.compile(loss = 'categorical_crossentropy',
                      optimizer = 'adam',
                      metrics = ['accuracy'])
  
        return model
    
    def load(self, model_filename):
        self.model = tf.keras.models.load_model(model_filename)
    
    def eval(self):
        pass
    
    def predict(self, source_file):
        path = exec2img(source_file)
        z=plt.imread(path)
        plt.imshow(z)

        img = tf.keras.utils.load_img(path, target_size=(150, 150))
        x = tf.keras.utils.img_to_array(img)
        x = np.expand_dims(x, axis=0) 
        classes = self.model.predict(x)
        classes = np.argmax(classes)

        #set the images labels
        label = ['Adialer.C', 'Agent.FYI', 'Allaple.A', 'Allaple.L', 'Alueron.gen!J', 'Autorun.K', 'C2LOP.P', 'C2LOP.gen!g', 'Dialplatform.B', 'Dontovo.A', 'Fakerean', 'Instantaccess', 'Lolyda.AA1', 'Lolyda.AA2', 'Lolyda.AA3', 'Lolyda.AT', 'Malex.gen!J', 'Obfuscator.AD', 'Rbot!gen', 'Skintrim.N', 'Swizzor.gen!E', 'Swizzor.gen!I', 'VB.AT', 'Wintrim.BX', 'Yuner.A']
        print(label[classes])
    
    def train(self, data_path, save_path):
        
        # splitfolders.ratio('/content/malimg_paper_dataset_imgs', output="/content/", seed=1337,
        
        os.chdir(data_path)
        
        #set the image size to 150
        img_size = 150
        #set the training data
        train = ImageDataGenerator().flow_from_directory(directory='train', target_size=(img_size,img_size), batch_size=10000)
        #set the validation data
        val = ImageDataGenerator().flow_from_directory(directory='val', target_size=(img_size,img_size), batch_size=10000)
        #set the testing data
        test = ImageDataGenerator().flow_from_directory(directory='test', target_size=(img_size,img_size), batch_size=10000)
    
        #load train images data and labels
        imgs_train, labels_train = next(train)
        #load validation images data and labels
        imgs_val, labels_val = next(val)
    
        Alexnet_model = Alexnet()
        #fit AlexNet model
        history_Alexnet = Alexnet_model.fit(imgs_train, 
                                           labels_train, 
                                           validation_data=(imgs_val, labels_val), 
                                           epochs=50)
        # save model
        Alexnet_model.save(save_path + "Alex.h5")
        
        #for plotting losses curve
        loss_training = history_Alexnet.history['loss']
        loss_test = history_Alexnet.history['val_loss']
    
        #for plotting accyracies curve
        accuracy_training = history_Alexnet.history['accuracy']
        accuracy_test = history_Alexnet.history['val_accuracy']
    
        loss_training = history_Alexnet.history['loss']
        loss_test = history_Alexnet.history['val_loss']
    
        accuracy_training = history_Alexnet.history['accuracy']
        accuracy_test = history_Alexnet.history['val_accuracy']
    
        #for Plotting
        plt.plot(loss_test)
        plt.plot(loss_training)
    
        #set the titles of losses plot
        plt.xlabel("# Of Epochs")
        plt.ylabel("Loss")
        plt.legend(['val Loss', 'Train Loss'])
        plt.show()
    
        #set the titles of accuracies plot
        plt.plot(accuracy_test)
        plt.plot(accuracy_training)
        plt.xlabel("# Of Epochs")
        plt.ylabel("Accuracy")
        plt.legend(['val accuracy', 'Train accuracy'])
        plt.show()
        

class VGG16():
    model = None
    
    def __init__(self):
        #build the VGG16 model
        vgg_model = VGG16(weights='imagenet',include_top=False, input_shape=(img_size,img_size,3),classes=25, pooling="avg")

        #make the layers trainable
        for layer in vgg_model.layers:
            layer.trainable = True

        #build the sequential model
        model_vgg = keras.models.Sequential()
        model_vgg.add(vgg_model)

        #add a flatten layer
        model_vgg.add(Flatten())

        #add dense layers
        model_vgg.add(Dense(128, activation='relu'))
        model_vgg.add(Dense(64, activation='relu'))

        #add softmax activation function to output layer
        model_vgg.add(Dense(25, activation='softmax'))

        #print the VGG16 model summary
        print(model_vgg.summary())

        #compile the VGG16 model 
        model_vgg.compile(loss='categorical_crossentropy', optimizer="adam", metrics=['accuracy'])
        return model_vgg

    def train(self, data_path, save_path) -> None:
        # 进入数据目录
        os.chdir(data_path)
        
        model = VGG16()
        
        # 拟合数据
        history_vgg= model.fit(imgs_train, labels_train, validation_data=(imgs_val, labels_val), epochs=50)
        
        # 保存模型
        model.save(save_path)

        #set the image size to 150
        img_size = 150
        #set the training data
        train = ImageDataGenerator().flow_from_directory(directory='train', target_size=(img_size,img_size), batch_size=10000)
        #set the validation data
        val = ImageDataGenerator().flow_from_directory(directory='val', target_size=(img_size,img_size), batch_size=10000)
        #set the testing data
        test = ImageDataGenerator().flow_from_directory(directory='test', target_size=(img_size,img_size), batch_size=10000)
    
        #load train images data and labels
        imgs_train, labels_train = next(train)
        #load validation images data and labels
        imgs_val, labels_val = next(val)
        
        #plot the losses curves
        loss_training = history_vgg.history['loss']
        loss_test = history_vgg.history['val_loss']

        #plot the accuracies curves
        accuracy_training = history_vgg.history['accuracy']
        accuracy_test = history_vgg.history['val_accuracy']

        loss_training = history_vgg.history['loss']
        loss_test = history_vgg.history['val_loss']

        accuracy_training = history_vgg.history['accuracy']
        accuracy_test = history_vgg.history['val_accuracy']

        #for Plotting
        plt.plot(loss_test)
        plt.plot(loss_training)

        #set the titles of the graph
        plt.xlabel("# Of Epochs")
        plt.ylabel("Loss")
        plt.legend(['val Loss', 'Train Loss'])
        plt.show()

        #set the titles of the graph
        plt.plot(accuracy_test)
        plt.plot(accuracy_training)
        plt.xlabel("# Of Epochs")
        plt.ylabel("Accuracy")
        plt.legend(['val accuracy', 'Train accuracy'])
        plt.show()
        
    def load(self, model_filename):
        self.model = tf.keras.models.load_model(model_filename)
        
    def predict(self, source_file :str) -> str:
        path = exec2img(source_file)
        z = plt.imread(path)
        plt.imshow(z)
    
        img = tf.keras.utils.load_img(path, target_size=(150, 150))
        x = tf.keras.utils.img_to_array(img)
        x = np.expand_dims(x, axis=0) 
        classes = self.model.predict(x)
        classes = np.argmax(classes)
    
        #set the images labels
        label = ['Adialer.C', 'Agent.FYI', 'Allaple.A', 'Allaple.L', 'Alueron.gen!J', 'Autorun.K', 'C2LOP.P', 'C2LOP.gen!g', 'Dialplatform.B', 'Dontovo.A', 'Fakerean', 'Instantaccess', 'Lolyda.AA1', 'Lolyda.AA2', 'Lolyda.AA3', 'Lolyda.AT', 'Malex.gen!J', 'Obfuscator.AD', 'Rbot!gen', 'Skintrim.N', 'Swizzor.gen!E', 'Swizzor.gen!I', 'VB.AT', 'Wintrim.BX', 'Yuner.A']
        return label[classes]
        
    def eval(self) -> str:
        pass