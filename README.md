BasKet Note Pads
================
Gleb Baryshev <gleb.baryshev@gmail.com>

Kelvie Wong <kelvie@ieee.org>

Purpose
-------
(From the original README by Sébastien)

This application provides as many baskets as you wish, and you can drag and drop
various objects (text, URLs, images, sounds...)  into its.

Objects can be edited, copied, dragged... So, you can arrange them as you want !

It's a DropDrawers clone (http://www.sigsoftware.com/dropdrawers/index.html) for
KDE 4.

Project Status
--------------
In the previous years, porting from KDE 3 to KDE 4 was generally finished.
However, some features remained not ported or became broken. Currently bug
fixing is under way.

Developers
-----------
As you may or may not have noticed, there isn't a user's section currently.
If you are reading this, chances are, you are a developer (if I'm wrong email me
;), so most of the developers documentation will go here until we can finalize a
user README after we're done porting.


Contact
-------
If you have any questions, or would like to contribute (always welcome!) please
send me an email to the  development mailing list at
basket-devel@lists.sourceforge.net.

Developers are usually idle on #basket-devel @ freenode on IRC, and it's quite
likely you'll catch one of us there Due to timezone differences, however, it's
generally better to email the list.

The BasKet web site is at:
https://launchpad.net/basket


Building/Installation
----------------------

To build and install BasKet, follow these steps (this assumes you have the relevant
kde4 development libraries and CMake):

```bash
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` -DKDE_INSTALL_QTPLUGINDIR=`qtpaths --plugin-dir` ..
make
# make install
```

Or you can try your luck with the installer script:

 `./installer`
