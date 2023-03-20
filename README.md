# copyicons - RetroFlow

A fork of [copyicons](https://github.com/cy33hc/copyicons) by [cy33hc](https://github.com/cy33hc)

This application is used for bulk copying of icon0.png/pic0.png from the ux0:app/GAME_ID/sce_sys to the ur0:appmeta/GAME_ID folder

The psvita can only load 500 bubbles. If you have more then 500 apps/games installed. The vita will not create the icon0.png and pic0.png files in the ur0:appmeta folder for those games that don't have bubbles.

**Modifications made to the original copyicons app**

In addition to copying the icon0.png/pic0.png to the appmeta folders, the app also copies additional images into the RetroFlow ux0 data folder.

* icon0 is copied to the RetroFlow ux0 data folder as a backup image for when the appmeta image isn't available.
* pic0 is also copied to the RetroFlow ux0 data folder for use as game background images.



## Features

1. Decrypt the icon0.png/pic0.png and copy to ur0:appmeta.
2. Like mentioned this app scans every game in the ux0:app folder and copies the icon0.png/pic0.png if it's not found in ur0:appmeta
3. Copy the icon0.png/pic0.png to the RetroFlow ux0 data folder named using the app TitleID as a filename.


## Useage
There is no release for this, the eboot is bundled in with the [RetroFlow](https://github.com/jimbob4000/RetroFlow-Launcher) app.

For use as a standalone vpk, the code would need to be modified to create directories outside of RetroFlow.

## Credits

cy33hc for the original [copyicons](https://github.com/cy33hc/copyicons) app.

Thx to theFlow for Vitashell. cy33hc copied the modules from Vitashell needed to pfs mount the game to decypt the content.
https://github.com/TheOfficialFloW/VitaShell
