#include <stdio.h>

#include "main.h"
#include "init.h"
#include "pfs.h"
#include "file.h"
#include "debugScreen.h"

#define printf psvDebugScreenPrintf
#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
	initCopyIcons();
	psvDebugScreenInit();

	SceUID dfd = sceIoDopen("ux0:app");
	if (dfd < 0)
		sceKernelExitProcess(0);

	int res = 0;
	char game_path[512];
	char pfs_path[512];
	char icon_path[512];
	char meta_icon_path[512];
	char pic_path[512];
	char meta_pic_path[512];
	char meta_path[512];

	// RetroFlow customisation
		char retroflow_icon_path[512];
		char retroflow_bg_path[512];
		char bg_path[512];
		char bg0_path[512];

	do {
		SceIoDirent dir;
		memset(&dir, 0, sizeof(SceIoDirent));

		res = sceIoDread(dfd, &dir);
		if (res > 0) {
			sprintf(game_path, "ux0:app/%s", dir.d_name);
			sprintf(meta_path, "ur0:appmeta/%s", dir.d_name);
			sprintf(pfs_path, "ux0:app/%s/sce_pfs", dir.d_name);
			sprintf(icon_path, "ux0:app/%s/sce_sys/icon0.png", dir.d_name);
			sprintf(meta_icon_path, "ur0:appmeta/%s/icon0.png", dir.d_name);
			sprintf(pic_path, "ux0:app/%s/sce_sys/pic0.png", dir.d_name);
			sprintf(meta_pic_path, "ur0:appmeta/%s/pic0.png", dir.d_name);

			// RetroFlow customisation
				sprintf(bg_path, "ux0:app/%s/sce_sys/livearea/contents/bg.png", dir.d_name);
				sprintf(bg0_path, "ux0:app/%s/sce_sys/livearea/contents/bg0.png", dir.d_name);

			printf("Looking for icons to copy for %s\n", dir.d_name);
			
			int pfs_path_exists = checkFolderExist(pfs_path);
			int icon_path_exists = checkFileExist(icon_path);
			int meta_icon_path_exists = checkFileExist(meta_icon_path);
			int pic_path_exists = checkFileExist(pic_path);
			int meta_pic_path_exists = checkFileExist(meta_pic_path);

			if (pfs_path_exists && ((icon_path_exists && !meta_icon_path_exists) || (pic_path_exists && !meta_pic_path_exists)))
			{
				createDirectory(meta_path);
				if (pfsMount(game_path) == 0)
				{
					if (icon_path_exists && !meta_icon_path_exists)
					{
						copyFile(icon_path, meta_icon_path, NULL);
						printf("copied %s to %s\n", icon_path, meta_icon_path);
					}

					if (pic_path_exists && !meta_pic_path_exists)
					{
						copyFile(pic_path, meta_pic_path, NULL);
						printf("copied %s to %s\n", pic_path, meta_pic_path);
					}
					pfsUmount();
				}
			}
			else if ((icon_path_exists && !meta_icon_path_exists) || (pic_path_exists && !meta_pic_path_exists))
			{
				createDirectory(meta_path);
				if (icon_path_exists && !meta_icon_path_exists)
				{
					copyFile(icon_path, meta_icon_path, NULL);
					printf("copied %s to %s\n", icon_path, meta_icon_path);
				}

				if (pic_path_exists && !meta_pic_path_exists)
				{
					copyFile(pic_path, meta_pic_path, NULL);
					printf("copied %s to %s\n", pic_path, meta_pic_path);
				}
			}

			// RetroFlow customisation

				// Copy icon and pic0
					sprintf(retroflow_icon_path, "ux0:data/RetroFlow/ICONS/Sony - PlayStation Vita/%s.png", dir.d_name);
					sprintf(retroflow_bg_path, "ux0:data/RetroFlow/BACKGROUNDS/Sony - PlayStation Vita/%s.png", dir.d_name);

					// Recheck meta folders
					int meta_icon_path_exists_after_copy = checkFileExist(meta_icon_path);
					int meta_pic_path_exists_after_copy = checkFileExist(meta_pic_path);

					// Check RetroFlow folders
					int retroflow_icon_path_exists = checkFileExist(retroflow_icon_path);
					int retroflow_bg_path_exists = checkFileExist(retroflow_bg_path);

					// Copy icon if missing from RetroFlow folder
					if (meta_icon_path_exists_after_copy && !retroflow_icon_path_exists)
					{
						copyFile(meta_icon_path, retroflow_icon_path, NULL);
						printf("copied %s to %s\n", meta_icon_path, retroflow_icon_path);
					}
					// Copy pic if missing from RetroFlow folder
					if (meta_pic_path_exists_after_copy && !retroflow_bg_path_exists)
					{
						copyFile(meta_pic_path, retroflow_bg_path, NULL);
						printf("copied %s to %s\n", meta_pic_path, retroflow_bg_path);
					}
					// Copy bg if pic missing from RetroFlow folder
					if (meta_pic_path_exists_after_copy && !retroflow_bg_path_exists)
					{
						copyFile(meta_pic_path, retroflow_bg_path, NULL);
						printf("copied %s to %s\n", meta_pic_path, retroflow_bg_path);
					}

				// Copy bg

					// // Check ux0 for bg pic
					// int bg_path_exists = checkFileExist(bg_path);

					// // Check RetroFlow folder for image
					// int retroflow_bg_path_exists_after_copy = checkFileExist(retroflow_bg_path);

					// // Copy bg if there's no image in the RetroFlow folder
					// if (pfs_path_exists && ((bg_path_exists && !retroflow_bg_path_exists_after_copy) || (bg_path_exists && !retroflow_bg_path_exists_after_copy)))
					// {
					// 	if (pfsMount(game_path) == 0)
					// 	{
					// 		if (bg_path_exists && !retroflow_bg_path_exists_after_copy)
					// 		{
					// 			copyFile(bg_path, retroflow_bg_path, NULL);
					// 			printf("copied %s to %s\n", bg_path, retroflow_bg_path);
					// 		}
					// 		pfsUmount();
					// 	}
					// }
					// else if ((bg_path_exists && !retroflow_bg_path_exists_after_copy) || (bg_path_exists && !retroflow_bg_path_exists_after_copy))
					// {
					// 	if (bg_path_exists && !retroflow_bg_path_exists_after_copy)
					// 	{
					// 		copyFile(bg_path, retroflow_bg_path, NULL);
					// 		printf("copied %s to %s\n", bg_path, retroflow_bg_path);
					// 	}
					// }

				// Copy bg0

					// // Check ux0 for bg0 pic
					// int bg0_path_exists = checkFileExist(bg0_path);

					// // Check RetroFlow folder for image
					// int retroflow_bg_path_exists_after_copy2 = checkFileExist(retroflow_bg_path);

					// // Copy bg0 if there's no image in the RetroFlow folder
					// if (pfs_path_exists && ((bg0_path_exists && !retroflow_bg_path_exists_after_copy2) || (bg0_path_exists && !retroflow_bg_path_exists_after_copy2)))
					// {
					// 	if (pfsMount(game_path) == 0)
					// 	{
					// 		if (bg0_path_exists && !retroflow_bg_path_exists_after_copy2)
					// 		{
					// 			copyFile(bg0_path, retroflow_bg_path, NULL);
					// 			printf("copied %s to %s\n", bg0_path, retroflow_bg_path);
					// 		}
					// 		pfsUmount();
					// 	}
					// }
					// else if ((bg0_path_exists && !retroflow_bg_path_exists_after_copy2) || (bg0_path_exists && !retroflow_bg_path_exists_after_copy2))
					// {
					// 	if (bg0_path_exists && !retroflow_bg_path_exists_after_copy2)
					// 	{
					// 		copyFile(bg0_path, retroflow_bg_path, NULL);
					// 		printf("copied %s to %s\n", bg0_path, retroflow_bg_path);
					// 	}
					// }

		}
	} while (res > 0);

	finishCopyIcons();
	sceKernelExitProcess(0);
	return 0;
}
