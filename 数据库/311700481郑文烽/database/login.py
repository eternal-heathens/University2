# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'login.ui'
#
# Created by: PyQt5 UI code generator 5.13.2
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgzets
import palyfair_cypehr
import pymssql
import student_jurisdiction


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(472, 372)
        self.account_number = QtWidgets.QLabel(Form)
        self.account_number.setGeometry(QtCore.QRect(90, 80, 41, 31))
        self.account_number.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.account_number.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.account_number.setObjectName("account_number")
        self.account_edit = QtWidgets.QLineEdit(Form)
        self.account_edit.setGeometry(QtCore.QRect(170, 80, 181, 31))
        self.account_edit.setObjectName("account_edit")
        self.password = QtWidgets.QLabel(Form)
        self.password.setGeometry(QtCore.QRect(90, 140, 41, 31))
        self.password.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.password.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.password.setObjectName("password")
        self.password_edit = QtWidgets.QLineEdit(Form)
        self.password_edit.setGeometry(QtCore.QRect(170, 140, 181, 31))
        self.password_edit.setObjectName("password_edit")
        self.password_edit.setEchoMode(QtWidgets.QLineEdit.Password)
        self.login = QtWidgets.QPushButton(Form)
        self.login.setGeometry(QtCore.QRect(90, 280, 75, 23))
        self.login.setObjectName("login")
        self.register_1 = QtWidgets.QPushButton(Form)
        self.register_1.setGeometry(QtCore.QRect(280, 280, 75, 23))
        self.register_1.setObjectName("register_1")
        self.rememeber = QtWidgets.QCheckBox(Form)
        self.rememeber.setGeometry(QtCore.QRect(150, 220, 191, 20))
        self.rememeber.setObjectName("rememeber")

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

        self.login.clicked.connect(self.log_in)
        self.register_1.clicked.connect(self.register)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "学生选课系统"))
        self.account_number.setToolTip(_translate("Form", "账号登陆"))
        self.account_number.setText(_translate("Form", "账号："))
        self.password.setToolTip(_translate("Form", "密码输入"))
        self.password.setText(_translate("Form", "密码："))
        self.login.setText(_translate("Form", "登陆"))
        self.register_1.setText(_translate("Form", "注册"))
        self.rememeber.setToolTip(_translate("Form", "记住账号密码，下次自动输入"))
        self.rememeber.setText(_translate("Form", "记住账号和密码"))

    def log_in(self):
        # 登陆
        ID = self.account_edit.text()
        password = self.password_edit.text()
        ID_corr_password = "SELECT password  FROM login WHERE ID = '%s'" % ID
        result = ''
        for ex in msg.ExecQuery(ID_corr_password):  # 将在数据库中读取的列表转为str
            result += str(ex)
        result = result[2:(3 + len(password))]
        test = palyfair_cypehr.decryption(result)
        self.ui_2 = QtWidgets.QDialog()
        child = student_jurisdiction.Ui_Dialog()
        child.setupUi(self.ui_2)
        if password == test:
            child.sno.setText(ID)
            self.ui_2.show()
        else:
            QtWidgets.QMessageBox.information(None, '登陆失败', '账号或密码错误，请重试！')

    def register(self):
        try:
            register_ID = self.account_edit.text()
            register_password = self.password_edit.text()
            cypher_password = palyfair_cypehr.encryption(register_password)
            register_sql = "INSERT INTO login VALUES('%s','%s')" % (register_ID, cypher_password)
            msg.Insert_ExecQuery(register_sql)
            QtWidgets.QMessageBox.information(None,'注册结果','注册成功！')
        except:
            QtWidgets.QMessageBox.information(None, '注册结果', '注册失败或者账号重复，请重试！')

class data_base:
    def __init__(self,server,user,password,database):
        self.server = server
        self.user = user
        self.password = password
        self.database = database

    def __GetConnect(self):
        # 得到数据库连接信息，返回conn.cursor()
        if not self.database:
            raise (NameError, "没有设置数据库信息")
        self.conn = pymssql.connect(server=self.server, user=self.user, password=self.password, database=self.database)
        cur = self.conn.cursor()
        if not cur:
            raise (NameError, "连接数据库失败")  # 将DBC信息赋值给cur
        else:
            return cur

    def ExecQuery(self, sql):
        '''
        执行查询语句
        返回一个包含tuple的list，list是元素的记录行，tuple记录每行的字段数值
        '''
        cur = self.__GetConnect()
        cur.execute(sql)  # 执行语句
        result = cur.fetchall()  # fetchall()获取查询结果
        # 查询完毕关闭数据库连接
        cur.close()
        self.conn.close()
        return result

    def Insert_ExecQuery(self, sql):
        '''
        执行插入语句
        返回一个bool 值
        '''
        cur = self.__GetConnect()
        cur.execute(sql)  # 执行语句
        # 查询完毕关闭数据库连接
        self.conn.commit()
        cur.close()
        self.conn.close()


msg = data_base(server='LAPTOP-8SJFQF62', user='sa', password='3318675zheng', database='MyDataBase')  # 数据库对象建立
