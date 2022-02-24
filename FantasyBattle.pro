QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Action/Action.cpp \
    Battle.cpp \
    Character/Boss.cpp \
    Character/Character.cpp \
    Character/Enemy.cpp \
    Character/Player.cpp \
    Character/StrongEnemy.cpp \
    Character/WeakEnemy.cpp \
    Floor.cpp \
    Item/DiamondArmor.cpp \
    Item/HPpotion.cpp \
    Item/IronArmor.cpp \
    Item/Item.cpp \
    Item/LeatherArmor.cpp \
    Item/MPpotion.cpp \
    Round.cpp \
    Skill/Blessing.cpp \
    Skill/Blood_sucking.cpp \
    Skill/Cursing.cpp \
    Skill/Defence.cpp \
    Skill/Greater_defence.cpp \
    Skill/Greater_strengthen.cpp \
    Skill/Regular_attack.cpp \
    Skill/Sharp_attack.cpp \
    Skill/Skill.cpp \
    Skill/Strengthen.cpp \
    Skill/Ultimate_strike.cpp \
    Tower.cpp \
    battlewindow.cpp \
    floorwindow.cpp \
    initialdialog.cpp \
    main.cpp \
    menuwindow.cpp \
    shopwindow.cpp

HEADERS += \
    Action/Action.h \
    Battle.h \
    Character/Boss.h \
    Character/Character.h \
    Character/Enemy.h \
    Character/Player.h \
    Character/StrongEnemy.h \
    Character/WeakEnemy.h \
    Floor.h \
    Item/DiamondArmor.h \
    Item/HPpotion.h \
    Item/IronArmor.h \
    Item/Item.h \
    Item/LeatherArmor.h \
    Item/MPpotion.h \
    Round.h \
    Skill/Blessing.h \
    Skill/Blood_sucking.h \
    Skill/Cursing.h \
    Skill/Defence.h \
    Skill/Greater_defence.h \
    Skill/Greater_strengthen.h \
    Skill/Regular_attack.h \
    Skill/Sharp_attack.h \
    Skill/Skill.h \
    Skill/Strengthen.h \
    Skill/Ultimate_strike.h \
    Tower.h \
    battlewindow.h \
    floorwindow.h \
    initialdialog.h \
    menuwindow.h \
    shopwindow.h

FORMS += \
    battlewindow.ui \
    floorwindow.ui \
    initialdialog.ui \
    menuwindow.ui \
    shopwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    sounds.qrc

DISTFILES += \
    images/Load Game.png \
    images/Load Game_hover.png \
    images/New Game.png \
    images/New Game_hover.png
