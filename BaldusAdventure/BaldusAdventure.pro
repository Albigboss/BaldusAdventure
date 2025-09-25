QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controleur/EnnemyType/bat.cpp \
    controleur/EnnemyType/ghost.cpp \
    controleur/EnnemyType/goblin.cpp \
    controleur/EnnemyType/skeleton.cpp \
    controleur/SpellType/spellarrow.cpp \
    controleur/SpellType/spelljump.cpp \
    controleur/SpellType/spellmelee.cpp \
    controleur/SpellType/spellshield.cpp \
    controleur/SpellType/spellspeed.cpp \
    controleur/SpellType/spellwaveh.cpp \
    controleur/SpellType/spellwavev.cpp \
    controleur/SpellType/spellwavevlarge.cpp \
    controleur/chest.cpp \
    controleur/door.cpp \
    controleur/enemy.cpp \
    controleur/entities.cpp \
    controleur/game.cpp \
    controleur/key.cpp \
    controleur/level.cpp \
    controleur/missiles.cpp \
    controleur/obstacle.cpp \
    controleur/player.cpp \
    controleur/shooterenemy.cpp \
    controleur/shop.cpp \
    controleur/spell.cpp \
    vue/losenwingui.cpp \
    main.cpp \
    maincontroller.cpp \
    vue/levelbonusgui.cpp \
    vue/pausegui.cpp \
    vue/gui.cpp \
    vue/levelgui.cpp \
    vue/menugui.cpp \
    vue/optiongui.cpp \
    vue/shopgui.cpp

HEADERS += \
    controleur/EnnemyType/bat.h \
    controleur/EnnemyType/ghost.h \
    controleur/EnnemyType/goblin.h \
    controleur/EnnemyType/skeleton.h \
    controleur/SpellType/spellarrow.h \
    controleur/SpellType/spelljump.h \
    controleur/SpellType/spellmelee.h \
    controleur/SpellType/spellshield.h \
    controleur/SpellType/spellspeed.h \
    controleur/SpellType/spellwaveh.h \
    controleur/SpellType/spellwavev.h \
    controleur/SpellType/spellwavevlarge.h \
    controleur/chest.h \
    controleur/door.h \
    controleur/enemy.h \
    controleur/entities.h \
    controleur/game.h \
    controleur/key.h \
    controleur/level.h \
    controleur/missiles.h \
    controleur/obstacle.h \
    controleur/player.h \
    controleur/shooterenemy.h \
    controleur/shop.h \
    controleur/spell.h \
    vue/losenwingui.h \
    maincontroller.h \
    vue/levelbonusgui.h \
    vue/pausegui.h \
    spelltype.h \
    vue/gui.h \
    vue/levelgui.h \
    vue/menugui.h \
    vue/optiongui.h \
    vue/shopgui.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ressources.qrc

