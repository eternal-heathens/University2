# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'student_jurisdiction.ui'
#
# Created by: PyQt5 UI code generator 5.13.2
#
# WARNING! All changes made in this file will be lost!


from PyQt5 import QtCore, QtGui, QtWidgets
import pymssql
class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(410, 304)
        self.select_student_information = QtWidgets.QPushButton(Dialog)
        self.select_student_information.setGeometry(QtCore.QRect(60, 40, 80, 20))
        self.select_student_information.setObjectName("select_student_-9*/8information")
        self.elective_course = QtWidgets.QPushButton(Dialog)
        self.elective_course.setGeometry(QtCore.QRect(60, 80, 75, 20))
        self.elective_course.setObjectName("elective_course")
        self.select_grade = QtWidgets.QPushButton(Dialog)
        self.select_grade.setGeometry(QtCore.QRect(230, 40, 80, 20))
        self.select_grade.setObjectName("select_grade")
        self.quit = QtWidgets.QPushButton(Dialog)
        self.quit.setGeometry(QtCore.QRect(230, 80, 75, 20))
        self.quit.setObjectName("quit")
        self.sno = QtWidgets.QLabel(Dialog)
        self.sno.setGeometry(QtCore.QRect(140, 20, 131, 16))
        self.sno.setObjectName("sno")
        self.elective_number = QtWidgets.QLineEdit(Dialog)
        self.elective_number.setGeometry(QtCore.QRect(200, 110, 131, 21))
        self.elective_number.setObjectName("elective_number")
        self.elective_num = QtWidgets.QLabel(Dialog)
        self.elective_num.setGeometry(QtCore.QRect(70, 120, 111, 16))
        self.elective_num.setObjectName("elective_num")
        self.output = QtWidgets.QTextBrowser(Dialog)
        self.output.setGeometry(QtCore.QRect(60, 140, 281, 161))
        self.output.setAutoFillBackground(False)
        self.output.setObjectName("output")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

        self.select_student_information.clicked.connect(self.select)
        self.select_grade.clicked.connect(self.select_g)
        self.elective_course.clicked.connect(self.elective)
        self.quit.clicked.connect(self.close)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "学生功能"))
        self.select_student_information.setText(_translate("Dialog", "查询个人信息"))
        self.elective_course.setText(_translate("Dialog", "选修"))
        self.select_grade.setText(_translate("Dialog", "查看成绩"))
        self.quit.setText(_translate("Dialog", "退出"))
        self.sno.setText(_translate("Dialog", "学号为："))
        self.elective_num.setText(_translate("Dialog", "输入选择/查询的课程号："))

    def select(self):
         try:
            ID = self.sno.text()
            select_information = "SELECT *  FROM student WHERE sno = %s" %ID
            information = msg.ExecQuery(select_information)
            self.output.setText(str(information))
         except:
            QtWidgets.QMessageBox.information(None, '结果', '查询失败，请重试！')

    def select_g(self):
         try:
            ID = self.sno.text()
            CNO = self.elective_number.text()
            select_information = "SELECT *  FROM elective WHERE sno = '%s' AND cno = '%s'" %(ID,CNO)
            information = msg.ExecQuery(select_information)
            self.output.setText(str(information))
         except:
            QtWidgets.QMessageBox.information(None, '结果', '成绩查询失败，请重试！')

    def elective(self):
        try:
            ID = self.sno.text()
            CNO = self.elective_number.text()
            elective_information = "INSERT INTO elective VALUES ('%s','%s',NULL)"%(ID,CNO)
            information = msg.Insert_ExecQuery(elective_information)
            QtWidgets.QMessageBox.information(None,'选修','选修成功')
        except:
            QtWidgets.QMessageBox.information(None,'选修','选修失败，请重新选择')

    def close(self):
        reslut = QtWidgets.QMessageBox.information(None,'确认','请问是否退出',QtWidgets.QMessageBox.Yes|QtWidgets.QMessageBox.No,QtWidgets.QMessageBox.Yes)
        if reslut == QtWidgets.QMessageBox.Yes:
            qApp = QtWidgets.QApplication.instance()
            qApp.quit()
        else:
            return

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