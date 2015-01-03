Générateur de photo d'identité
==============================
Ce programme a pour but de simplifier la réalisation de photos d'identités. Ainsi on prend une photo (ou on en importe une) on localise le visage de la personne et on génère ainsi directement une planche avec quatre photos prêtes à être imprimées.

Pour plus d'information reportez vous à la page web associée à ce projet : http://karlito139.github.com/generateur-de-photo-identite.



Installation
============
Pour compiler ce logiciel il vous faudra tout d'abord avoir installé la librairie QT ainsi que opencv. Une fois ceci fait, si vous êtes sous windows il faudra modifier le fichier .pro pour indiquer où se trouve votre librairie opencv.

Une fois tout installé vous pourez configurer le projet :

	qmake

Puis le compiler :

	make


Développement
=============
Pour configurer QT pour pouvoir développer sur cette application il faut pkg-config trouve opencv. De base sous ubuntu il faut réaliser la manipulation suivante :

Créer le fichier : /usr/local/lib/pkgconfig/opencv.pc

Y écrire :

	prefix=/usr
	exec_prefix=${prefix}
	includedir=${prefix}/include
	libdir=${exec_prefix}/lib

	Name: opencv
	Description: The opencv library
	Version: 2.x.x
	Cflags: -I${includedir}/opencv -I${includedir}/opencv2
	Libs: -L${libdir} -lopencv_calib3d -lopencv_imgproc -lopencv_contrib -lopencv_legacy -lopencv_core -lopencv_ml -lopencv_features2d -lopencv_objdetect -lopencv_flann -lopencv_video -lopencv_highgui

Enregistrer puis l'ajouter au path de pkg-config :

	PKG_CONFIG_PATH=$PKG_CONFIG_PATH:/usr/local/lib/pkgconfig
	export PKG_CONFIG_PATH

Ces deux dernières lignes sont à ajouter à votre .bashrc pour automatiser l'insertion d'opencv au path à chaque reboot.

Malgrè cela il est possible de toujours avoir des problèmes pour compiler les fichier nécessitant highgui. Il suffit d'installer le paquet correspondant :

	sudo apt-get install libhighgui-dev
