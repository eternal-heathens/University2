import sys
import login
from PyQt5 import QtCore, QtGui, QtWidgets


if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    widget = QtWidgets.QWidget()
    ui = login.Ui_Form()
    ui.setupUi(widget)
    widget.show()
    sys.exit(app.exec_())