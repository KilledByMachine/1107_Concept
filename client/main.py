import sys
import os

from PySide2.QtGui import QGuiApplication
from PySide2.QtQml import QQmlApplicationEngine
from PySide2.QtCore import QObject, Slot

from Button_Controller import Button_Controller


if __name__ == "__main__":
    app = QGuiApplication(sys.argv)

    button_controller = Button_Controller()

    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("button_controller", button_controller)
    engine.load(os.path.join(os.path.dirname(__file__) + os.sep + "resources" + os.sep + "layouts", "authorization.qml"))

    if not engine.rootObjects():
        sys.exit(-1)
    sys.exit(app.exec_())


# TODO:
# 1. Зробити перевірку залогованість користувача, і якщо користувач залогований то не 
# завантажувати welcome.qml
