import sys, os
from PyQt6.QtCore import (QStringListModel, QDir)
from PyQt6.QtCore import QThread, QObject, pyqtSignal, QMutex, QTimer
from PyQt6.QtWidgets import (
    QVBoxLayout,
    QMainWindow,
    QWidget,
    QApplication,
    QTableWidget,
    QTableWidgetItem,
    QListWidgetItem,
    QDialog,
    QMessageBox,
    QPushButton,
    QLineEdit,
    QListView,
    QFileDialog,
    QProgressDialog,
    QAbstractItemView,
    QHeaderView,
    QLabel
)

from View import UI_main

class MainWindow(UI_main.Ui_MainWindow, QWidget):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)
        self.init_ui()
        self.init_slot()
        
    def init_ui(self):
        self.setWindowTitle("基于深度学习的恶意代码检测工具")
        
        # Disable the button before data soure is ok
        self.pushButton_model_train.setEnabled(False)
        self.pushButton_model_predict.setEnabled(False)
    
    def init_slot(self):
        # page train
        self.pushButton_choose_source_data_dir.clicked.connect(
            lambda x: self.pushButton_choose_source_data_dir_clicked()
        )
        self.pushButton_choose_dest_model_dir.clicked.connect(
            lambda x: self.pushButton_choose_dest_model_dir_clicked()
        )
        self.pushButton_model_train.clicked.connect(
            lambda x: self.pushButton_model_train_clicked()
        )
        self.pushButton_mode_load.clicked.connect(
            lambda x: self.pushButton_model_load_clicked()
        )
        
        # page predict
        self.pushButton_suspicious_file_upload.clicked.connect(
            lambda x: self.pushButton_suspicious_file_upload_clicked()
        )
        self.pushButton_model_predict.clicked.connect(
            lambda x: self.pushButton_model_predict_clicked()
        )

    def import_file(self) -> str:
        fdlg = QFileDialog()
        fdlg.setFileMode(QFileDialog.FileMode.AnyFile)
        
        if fdlg.exec():
            #接受选中文件的路径，默认为列表
            filenames = fdlg.selectedFiles()
            #列表中的第一个元素即是文件路径，以只读的方式打开文件
            return filenames[0]
        
    def import_dir(self) -> str:
        fdlg = QFileDialog()
        fdlg.setFileMode(QFileDialog.FileMode.Directory)
        
        if fdlg.exec():
            #接受选中文件的路径，默认为列表
            filenames = fdlg.selectedFiles()
            #列表中的第一个元素即是文件路径，以只读的方式打开文件
            return filenames[0]
        
    def pushButton_model_predict_clicked(self):
        suspicious_filename = self.lineEdit_suspicious.text()
        
        if self.comboBox_selected_model_predict.currentText() == "AlexNet":
            from CNN.model import Alexnet as model
            result = model.predict(suspicious_filename)
            self.listWidget_mode_predict_output.addItem(result)
        if self.comboBox_selected_model_predict.currentText() == "VGG16":
            from CNN.model import VGG16 as model
            result = model.predict(suspicious_filename)
            self.listWidget_mode_predict_output.addItem(result)
        
    def pushButton_model_load_clicked(self):
        model_filename = self.import_file()
        self.lineEdit_selected_model_filename.setText(model_filename)
        
        if self.comboBox_selected_model_predict.currentText() == "AlexNet":
            from CNN.model import Alexnet as model
            try:
                model.load(model_filename)
            except Exception as e:
                msgBox = QMessageBox()
                msgBox.setText("Load model failed")
                result = msgBox.exec()
            
        if self.comboBox_selected_model_predict.currentText() == "VGG16":
            from CNN.model import VGG16 as model
            try:
                model.load(model_filename)
            except Exception as e:
                msgBox = QMessageBox()
                msgBox.warning("Load module failed")
                result = msgBox.exec()
            
        self.pushButton_model_predict.setEnabled(True)
        
    # pushButton triggered function
    def pushButton_suspicious_file_upload_clicked(self):
        suspicious_filename = self.import_file()
        self.lineEdit_suspicious.setText(suspicious_filename)
    
    def pushButton_choose_source_data_dir_clicked(self):
        dirname = self.import_dir()
        
        if len(dirname) < 1 or not os.path.isdir(dirname):
            msgBox = QMessageBox()
            msgBox.setText("Invalid directory")
            # msgBox.buttonClicked.connect(msgButtonClick)

            returnValue = msgBox.exec()
            if returnValue == QMessageBox.StandardButton.Ok:
               self.pushButton_model_train.setEnabled(True)
               # print('OK clicked')
               pass
            
        self.lineEdit_datasource.setText(dirname)
    
    def pushButton_choose_dest_model_dir_clicked(self):
        model_name = self.import_dir()
        
        if os.path.exists(model_name):
            msgBox = QMessageBox()
            msgBox.setText("Model already exist, are you going to override it?")
            
            returnValue = msgBox.exec()
            if returnValue == QMessageBox.StandardButton.Ok:
               # print('OK clicked')
               self.pushButton_model_train.setEnabled(True)
               pass
        
        self.lineEdit_model_dest.setText(model_name)
        
    def pushButton_model_train_clicked(self):
        if self.comboBox_selected_model_train.currentText() == "AlexNet":
            from CNN.model import Alexnet as model
            
            self.listWidget_train_state.addItem(QListWidgetItem("Start to train Alexnet model"))
            # model.train()
            
        if self.comboBox_selected_model_train.currentText() == "VGG16":
            from CNN.model import VGG16 as model
            self.listWidget_train_state.addItem(QListWidgetItem("Start to train VGG16 model"))
            # model.train()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MainWindow()
    w.show()
    sys.exit(app.exec())
