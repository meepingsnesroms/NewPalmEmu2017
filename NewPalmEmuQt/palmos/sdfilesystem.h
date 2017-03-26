#ifndef SDFILESYSTEM_H
#define SDFILESYSTEM_H

#define vfsTrapInit						0
#define vfsTrapCustomControl			1

#define vfsTrapFileCreate				2
#define vfsTrapFileOpen					3
#define vfsTrapFileClose				4
#define vfsTrapFileReadData				5
#define vfsTrapFileRead					6
#define vfsTrapFileWrite				7
#define vfsTrapFileDelete				8
#define vfsTrapFileRename				9
#define vfsTrapFileSeek					10
#define vfsTrapFileEOF					11
#define vfsTrapFileTell					12
#define vfsTrapFileResize				13
#define vfsTrapFileGetAttributes		14
#define vfsTrapFileSetAttributes		15
#define vfsTrapFileGetDate				16
#define vfsTrapFileSetDate				17
#define vfsTrapFileSize					18

#define vfsTrapDirCreate				19
#define vfsTrapDirEntryEnumerate		20
#define vfsTrapGetDefaultDirectory		21
#define vfsTrapRegisterDefaultDirectory	22
#define vfsTrapUnregisterDefaultDirectory	23

#define vfsTrapVolumeFormat				24
#define vfsTrapVolumeMount				25
#define vfsTrapVolumeUnmount			26
#define vfsTrapVolumeEnumerate			27
#define vfsTrapVolumeInfo				28
#define vfsTrapVolumeGetLabel			29
#define vfsTrapVolumeSetLabel			30
#define vfsTrapVolumeSize				31

#define vfsTrapInstallFSLib				32
#define vfsTrapRemoveFSLib				33
#define vfsTrapImportDatabaseFromFile	34
#define vfsTrapExportDatabaseToFile		35
#define vfsTrapFileDBGetResource		36
#define vfsTrapFileDBInfo				37
#define vfsTrapFileDBGetRecord			38

#define vfsTrapImportDatabaseFromFileCustom	39
#define vfsTrapExportDatabaseToFileCustom		40

// System use only
#define vfsTrapPrivate1					41

#define vfsMaxSelector					vfsTrapPrivate1



#define vfsIteratorStart              0x0
#define vfsIteratorStop               0xFFFFFFFF

#define	vfsInvalidVolRef		0
//constant for an invalid volume reference, guaranteed not to represent a valid one.
//Use it like you would use NULL for a FILE*.
#define	vfsInvalidFileRef		0
//constant for an invalid file reference, guaranteed not to represent a valid one.
//Use it like you would use NULL for a FILE*.

void filesystemdispatch();

#endif // SDFILESYSTEM_H
