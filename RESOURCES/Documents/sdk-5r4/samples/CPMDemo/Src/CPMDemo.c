/******************************************************************************
 *
 * Copyright (c) 1994-2002 PalmSource, Inc. All rights reserved.
 *
 * File: CPMDemo.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 *****************************************************************************/

#include <PalmOS.h>
#include "CPMDemoRsc.h"

#include "CPMLib.h"


/***********************************************************************
 *
 *	Entry Points
 *
 ***********************************************************************/


/***********************************************************************
 *
 *	Internal Structures
 *
 ***********************************************************************/
typedef struct
	{
	UInt8 replaceme;
	} StarterPreferenceType;

typedef struct _PrvKeyInfoTag {
    APKeyInfoType           keyinfo;
    struct _PrvKeyInfoTag   *next;
} KeyInfoListType;

typedef enum {
  ACTION_HASH = 1,
  ACTION_ENCRYPT,
  ACTION_DECRYPT,
  ACTION_SIGN,
  ACTION_VERIFY,
  ACTION_KEYGEN
} ActionEnum;

typedef struct {
	UInt16 cpmLibRef;
	UInt32 hContext;
	UInt16 numProviders;

	APProviderInfoType      *providerInfoList;
	UInt32                  *providerIDList;
	Char                    **providerStringList;

	Int16                   selectedProvider;

	Char                    *actionStringList[6];

	KeyInfoListType         *keyinfoList;
	Char                    **keyStringList;
	UInt16                  keyStringSize;

	ActionEnum                  currentAction;


} CPMDemoAppInfoType;

typedef CPMDemoAppInfoType* CPMDemoAppInfoPtr;


/***********************************************************************
 *
 *	Global variables
 *
 ***********************************************************************/
//static Boolean HideSecretRecords;
static CPMDemoAppInfoType   appinfo;
static Char                 gBuffer[256];

static UInt8                gEncryptedBuffer[256];
static UInt32               gEncryptedBufferSize = 256;
static UInt8                gDecryptedBuffer[256];
static UInt32               gDecryptedBufferSize = 256;

static Boolean              gEncrypted = false;

/***********************************************************************
 *
 *	Global Constants
 *
 ***********************************************************************/
static Char                 kSignString[]       = "Sign";
static Char                 kVerifyString[]     = "Verify";
static Char                 kEncryptString[]    = "Encrypt";
static Char                 kDecryptString[]    = "Decrypt";
static Char                 kHashString[]       = "Hash";
static Char                 kKeysString[]       = "Keys";

static Char                 kEncryptBuffer[]    = "Ricardo Lagos";

static Char                 kUsageTypeString[8][32] = {
  "Unspecified",
  "Signing",
  "Encryption",
  "Certificate Signing",
  "Key Encrypting",
  "Data  Encrypting",
  "Messag Integrity",
  "All"
};

static Char                 kAlgorithmTypeString[50][32] = {
    "apAlgorithmTypeUnspecified",

    /* block ciphers */
    "SymmetricTypeDES",
    "SymmetricTypeRC2",
    "SymmetricTypeRC4",
    "SymmetricTypeRC5",
    "SymmetricTypeRC6",
    "SymmetricTypeDESX_XDX3",
    "SymmetricType3DES_EDE2",
    "SymmetricType3DES_EDE3",
    "SymmetricTypeIDEA",
    "SymmetricTypeDiamond2",
    "SymmetricTypeBlowfish",
    "SymmetricTypeTEA",
    "SymmetricTypeSAFER",
    "SymmetricType3WAY",
    "SymmetricTypeGOST",
    "SymmetricTypeSHARK",
    "SymmetricTypeCAST128",
    "SymmetricTypeSquare",
    "SymmetricTypeSkipjack",

    /* stream ciphers */
    "SymmetricTypePanama",
    "SymmetricTypeARC4",
    "SymmetricTypeSEAL",
    "SymmetricTypeWAKE",
    "SymmetricTypeSapphire",
    "SymmetricTypeBBS",

    /* AES block ciphers */
    "SymmetricTypeRijndael",
    "SymmetricTypeCAST256",
    "SymmetricTypeTwofish",
    "SymmetricTypeMARS",
    "SymmetricTypeSerpent",

    /* asymmetric key types */
    "AsymmetricTypeRSA",
    "AsymmetricTypeDSA",
    "AsymmetricTypeElgamal",
    "AsymmetricTypeNR",           /* Nyberg-Rueppel */
    "AsymmetricTypeBlumGoldwasser",
    "AsymmetricTypeRabin",
    "AsymmetricTypeRW",           /* Rabin-Williams */
    "AsymmetricTypeLUC",
    "AsymmetricTypeLUCELG",

    /* elliptic curve */
    "AsymmetricTypeECDSA",
    "AsymmetricTypeECNR",
    "AsymmetricTypeECIES",
    "AsymmetricTypeECDHC",
    "AsymmetricTypeECMQVC",

    /* key agreement */
    "KeyAgreementTypeDH",
    "KeyAgreementTypeDH2",        /* Unified Diffie-Hellman */
    "KeyAgreementTypeMQV",        /* Menezes-Qu-Vanstone */
    "KeyAgreementTypeLUCDIF",
    "KeyAgreementTypeXTRDH"
};



/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/
#define appFileCreator			'STRT'	// register your own at http://www.palmos.com/dev/creatorid/
#define appVersionNum			0x01
#define appPrefID				0x00
#define appPrefVersionNum		0x01

// Define the minimum OS version we support (2.0 for now).
#define ourMinVersion	sysMakeROMVersion(2,0,0,sysROMStageRelease,0)
#define kPalmOS10Version	sysMakeROMVersion(1,0,0,sysROMStageRelease,0)


/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/


/***********************************************************************
 *
 * FUNCTION:    RomVersionCompatible
 *
 * DESCRIPTION: This routine checks that a ROM version is meet your
 *              minimum requirement.
 *
 * PARAMETERS:  requiredVersion - minimum rom version required
 *                                (see sysFtrNumROMVersion in SystemMgr.h
 *                                for format)
 *              launchFlags     - flags that indicate if the application
 *                                UI is initialized.
 *
 * RETURNED:    error code or zero if rom is compatible
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags)
{
	UInt32 romVersion;

	// See if we're on in minimum required version of the ROM or later.
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if (romVersion < requiredVersion)
		{
		if ((launchFlags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
			{
			FrmAlert (RomIncompatibleAlert);

			// Palm OS 1.0 will continuously relaunch this app unless we switch to
			// another safe one.
			if (romVersion <= kPalmOS10Version)
				{
				AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
				}
			}

		return sysErrRomIncompatible;
		}

	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    GetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 *
 * PARAMETERS:  formId - id of the form to display
 *
 * RETURNED:    void *
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void * GetObjectPtr(UInt16 objectID)
{
	FormPtr frmP;

	frmP = FrmGetActiveForm();
	return FrmGetObjectPtr(frmP, FrmGetObjectIndex(frmP, objectID));
}

/***************
 *
 ***************/
static void SelectProvider(Int16 selection)
{
    ControlPtr      buttonP;

    // Choice is the index into the provider list stuff
    appinfo.selectedProvider = selection;

    buttonP = GetObjectPtr(MainProviderMoreButton);
    CtlSetUsable(buttonP, true);
    CtlDrawControl(buttonP);

    buttonP = GetObjectPtr(MainSetDefaultButton);
    CtlSetUsable(buttonP, true);
    CtlDrawControl(buttonP);
}

static void ProviderMoreInfoFlag(UInt32 flags, UInt32 xflag, UInt16 objectID)
{
    FormPtr         frmP        = NULL;
    Boolean         value       = false;
    UInt16          objectindex = 0;

    frmP = FrmGetActiveForm();
    objectindex = FrmGetObjectIndex(frmP, objectID);

    if (flags & xflag) {
        value = true;
    }

    FrmSetControlValue(frmP, objectindex, value);
}

static void ProviderMoreInfo(void)
{
    FormPtr     oldfrmP;
    FormPtr     frmP;
    UInt32      flags;
    Char        *name;
    Char        *description;
    UInt16      numAlgs         = 0;
    FieldPtr    fieldP;
    Char        buffer[8];

    // Initialize the new form
    oldfrmP = FrmGetActiveForm();
    frmP = FrmInitForm(ProviderInfoForm);
    FrmSetActiveForm(frmP);

    name = appinfo.providerInfoList[appinfo.selectedProvider].name;
    description = appinfo.providerInfoList[appinfo.selectedProvider].other;
    flags = appinfo.providerInfoList[appinfo.selectedProvider].flags;
    numAlgs = appinfo.providerInfoList[appinfo.selectedProvider].numAlgorithms;

    // Set the provider name
    fieldP = GetObjectPtr(ProviderInfoNameField);
    FldSetTextPtr(fieldP, name);

    // Set the description
    fieldP = GetObjectPtr(ProviderInfoDescriptionField);
    FldSetTextPtr(fieldP, description);

    // Set the number of algorithms
    StrIToA(buffer, numAlgs);
    fieldP = GetObjectPtr(ProviderInfoNumAlgsField);
    FldSetTextPtr(fieldP, buffer);

    // Evaluate the flags
    ProviderMoreInfoFlag(flags, APF_MP, ProviderInfoMPCheckbox);
    ProviderMoreInfoFlag(flags, APF_HW, ProviderInfoHWCheckbox);
    ProviderMoreInfoFlag(flags, APF_HASH, ProviderInfoHashCheckbox);
    ProviderMoreInfoFlag(flags, APF_CIPHER, ProviderInfoEncryptCheckbox);
    ProviderMoreInfoFlag(flags, APF_CIPHER, ProviderInfoDecryptCheckbox);
    ProviderMoreInfoFlag(flags, APF_SIGN, ProviderInfoSignCheckbox);
    ProviderMoreInfoFlag(flags, APF_VERIFY, ProviderInfoVerifyCheckbox);
    ProviderMoreInfoFlag(flags, APF_KEYGEN, ProviderInfoKeysCheckbox);

    // Display The Form
    FrmDoDialog(frmP);

    // Delete Form
    FrmDeleteForm(frmP);

    // Set the old form back as active
    FrmSetActiveForm(oldfrmP);
}

static void ProviderSetDefault(void)
{
    UInt32      providerID      = 0;
    Err         err;

    providerID = appinfo.providerIDList[appinfo.selectedProvider];

    err = CPMLibSetDefaultProvider(appinfo.cpmLibRef, providerID);

    if (err == cpmErrUnimplemented) {
        StrPrintF(gBuffer, "Cannot set provider as default, this function has not been implemented");
        FrmCustomAlert(ErrorAlert, gBuffer, NULL, NULL);
    } else if (err != errNone) {
        StrPrintF(gBuffer, "Cannot set provider as default: 0x%x", err);
        FrmCustomAlert(ErrorAlert, gBuffer, NULL, NULL);
    }

}

static void ShowKeysList(void)
{
    ListPtr             listP;
    FormPtr             formP;

    Char                **keyStringList;
    UInt32              counter;
    KeyInfoListType     *keyinfonode;
    Char                *keyName;

    formP = FrmGetActiveForm();
    listP = GetObjectPtr(MainKeysList);
    keyStringList = appinfo.keyStringList;

    if (appinfo.keyStringList != NULL) {

        LstSetListChoices(listP, NULL, 0);

        for (counter = 0; counter < appinfo.keyStringSize; counter++) {
            MemPtrFree(appinfo.keyStringList[counter]);
        }

        MemPtrFree(appinfo.keyStringList);
    }

    // Count how many keys we have
    counter = 0;
    keyinfonode = appinfo.keyinfoList;
    while (keyinfonode != NULL) {
        counter = counter + 1;
        keyinfonode = keyinfonode->next;
    }

    // allocate the string  list
    appinfo.keyStringSize = counter;
    appinfo.keyStringList = (Char **)MemPtrNew(sizeof(Char *) * counter);

    for (counter = 0; counter < appinfo.keyStringSize; counter++) {
        keyName = (Char *)MemPtrNew(sizeof(Char) * 8);

        StrPrintF(keyName, "Key %ld", (counter + 1));
        appinfo.keyStringList[counter] = keyName;
    }

    // Set the string list into the lsit
    LstSetListChoices(listP, appinfo.keyStringList, appinfo.keyStringSize);
    LstSetSelection(listP, -1);

    FrmShowObject(formP, FrmGetObjectIndex(formP, MainKeysList));
}

static void HideKeysList()
{
    FormPtr             formP;

    formP = FrmGetActiveForm();

    FrmHideObject(formP, FrmGetObjectIndex(formP, MainKeysList));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainKeyMoreButton));
}

static void ShowKeysButtons()
{
    FormPtr             formP;
    ListPtr             listP;
    Int16               selection;

    formP = FrmGetActiveForm();
    listP = GetObjectPtr(MainKeysList);

    FrmShowObject(formP, FrmGetObjectIndex(formP, MainGenerateKeyButton));
    FrmShowObject(formP, FrmGetObjectIndex(formP, MainImportKeyButton));

    selection = LstGetSelection(listP);

    if (selection != -1) {
        FrmShowObject(formP, FrmGetObjectIndex(formP, MainReleaseKeyButton));
        FrmShowObject(formP, FrmGetObjectIndex(formP, MainExportKeyButton));
    }
}

static void HideKeysButtons()
{
    FormPtr             formP;

    formP = FrmGetActiveForm();

    FrmHideObject(formP, FrmGetObjectIndex(formP, MainGenerateKeyButton));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainImportKeyButton));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainReleaseKeyButton));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainExportKeyButton));
}

static void ShowEncryptButtons()
{
    FormPtr             formP;
    ListPtr             listP;
    Int16               selection;

    formP = FrmGetActiveForm();
    listP = GetObjectPtr(MainKeysList);

    FrmShowObject(formP, FrmGetObjectIndex(formP, MainEncryptLabel));
    FrmShowObject(formP, FrmGetObjectIndex(formP, MainEncryptBufferField));

    selection = LstGetSelection(listP);

    if (selection != -1) {
        FrmShowObject(formP, FrmGetObjectIndex(formP, MainEncryptButton));
    }

    FrmShowObject(formP, FrmGetObjectIndex(formP, MainEncryptedCheckbox));

    if (gEncrypted) {
        FrmShowObject(formP, FrmGetObjectIndex(formP, MainClearEncryptBufferButton));
    }
}

static void HideEncryptButtons()
{
    FormPtr             formP;

    formP = FrmGetActiveForm();

    FrmHideObject(formP, FrmGetObjectIndex(formP, MainEncryptLabel));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainEncryptBufferField));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainEncryptButton));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainEncryptedCheckbox));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainClearEncryptBufferButton));

}

static void ShowDecryptButtons()
{
    FormPtr             formP;
    ListPtr             listP;
    Int16               selection;

    formP = FrmGetActiveForm();
    listP = GetObjectPtr(MainKeysList);

    FrmShowObject(formP, FrmGetObjectIndex(formP, MainDecryptLabel));
    FrmShowObject(formP, FrmGetObjectIndex(formP, MainDecryptField));

    selection = LstGetSelection(listP);

    if ((selection != -1) && gEncrypted) {
        FrmShowObject(formP, FrmGetObjectIndex(formP, MainDecryptButton));
    }

    FrmShowObject(formP, FrmGetObjectIndex(formP, MainEncryptedCheckbox));

    if (gEncrypted) {
        FrmShowObject(formP, FrmGetObjectIndex(formP, MainClearEncryptBufferButton));
    }
}

static void HideDecryptButtons()
{
    FormPtr             formP;
    FieldPtr            fieldP;

    formP = FrmGetActiveForm();
    fieldP = GetObjectPtr(MainDecryptField);

    FldSetTextPtr(fieldP, NULL);

    FrmHideObject(formP, FrmGetObjectIndex(formP, MainDecryptLabel));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainDecryptField));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainDecryptButton));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainEncryptedCheckbox));
    FrmHideObject(formP, FrmGetObjectIndex(formP, MainClearEncryptBufferButton));
}

static void SelectAction(Int16 selection)
{
    ListPtr         listP;
    static Int16    oldSelection = -1;
    Char            *selectionText;

    listP = GetObjectPtr(MainActionList);

    if (oldSelection != -1) {
        // Hide the old UI stuff
        selectionText = LstGetSelectionText(listP, oldSelection);

        // Now depending on what the selection text is, show those UI elements
        if (StrCompare(selectionText, kSignString) == 0) {
            HideKeysList();
        }

        if (StrCompare(selectionText, kVerifyString) == 0) {
            HideKeysList();
        }

        if (StrCompare(selectionText, kEncryptString) == 0) {
            HideKeysList();
            HideEncryptButtons();
        }

        if (StrCompare(selectionText, kDecryptString) == 0) {
            HideKeysList();
            HideDecryptButtons();
        }

        if (StrCompare(selectionText, kHashString) == 0) {
            HideKeysList();
        }

        if (StrCompare(selectionText, kKeysString) == 0) {
            // Keys UI
            HideKeysList();
            HideKeysButtons();
        }
    }

    // Show the new UI stuff
    selectionText = LstGetSelectionText(listP, selection);
    oldSelection = selection;

    // Now depending on what the selection text is, show those UI elements
    if (StrCompare(selectionText, kSignString) == 0) {
        appinfo.currentAction = ACTION_SIGN;
        ShowKeysList();
    }

    if (StrCompare(selectionText, kVerifyString) == 0) {
        appinfo.currentAction = ACTION_VERIFY;
        ShowKeysList();
    }

    if (StrCompare(selectionText, kEncryptString) == 0) {
        appinfo.currentAction = ACTION_ENCRYPT;
        ShowKeysList();
        ShowEncryptButtons();
    }

    if (StrCompare(selectionText, kDecryptString) == 0) {
        appinfo.currentAction = ACTION_DECRYPT;
        ShowKeysList();
        ShowDecryptButtons();
    }

    if (StrCompare(selectionText, kHashString) == 0) {
        appinfo.currentAction = ACTION_SIGN;
        ShowKeysList();
    }

    if (StrCompare(selectionText, kKeysString) == 0) {
        appinfo.currentAction = ACTION_KEYGEN;
        ShowKeysList();
        ShowKeysButtons();
    }

}

static void GenerateKey()
{
    FormPtr         oldfrmP;
    FormPtr         frmP;
    UInt16          buttonhit;

    ListPtr         algorithmlistP;
    ListPtr         usagelistP;

    Boolean         redraw          = false;

    oldfrmP = FrmGetActiveForm();

    // Initialize the create key form
    frmP = FrmInitForm(GenerateKeyForm);
    FrmSetActiveForm(frmP);

    // Get List Ptrs
    algorithmlistP = GetObjectPtr(GenerateKeyAlgorithmList);
    usagelistP = GetObjectPtr(GenerateKeyUsageList);

    LstSetSelection(algorithmlistP, -1);
    LstSetSelection(usagelistP, -1);

    // Show form
    buttonhit = FrmDoDialog(frmP);

    // Now read what the user entered -- unless they canceled the usage
    if (buttonhit == GenerateKeyOKButton) {
        Int16           algtype;
        Int16           keyusage;
        KeyInfoListType *keyinfonodeP;
        KeyInfoListType *insert;
        Err             err;
        UInt8           *keydata;
        UInt32          datalen;

        FieldPtr        fieldP;

        fieldP = GetObjectPtr(GenerateKeyKeyDataField);

        algtype = LstGetSelection(algorithmlistP);
        keyusage = LstGetSelection(usagelistP);

        if (algtype == -1) {
            FrmCustomAlert(ErrorAlert, "You must select an algorithm type before generating a key!", NULL, NULL);
            goto cleanup;
        }

        if (keyusage == -1) {
            FrmCustomAlert(ErrorAlert, "You must select a key usage type before generating a key!", NULL, NULL);
            goto cleanup;
        }

        keydata = (UInt8 *)FldGetTextPtr(fieldP);
        if (keydata == NULL) {
            FrmCustomAlert(ErrorAlert, "You must enter some keydata before generating a key!", NULL, NULL);
            goto cleanup;
        }
        datalen = StrLen((Char *)keydata);

        keyinfonodeP = (KeyInfoListType *)MemPtrNew(sizeof(KeyInfoListType));
        MemSet(keyinfonodeP, sizeof(KeyInfoListType), 0);
        keyinfonodeP->keyinfo.type = (APAlgorithmEnum)(algtype + 1);
        keyinfonodeP->keyinfo.usage = (APKeyUsageEnum)(keyusage + 1);
        err = CPMLibGenerateKey(appinfo.cpmLibRef, keydata, datalen, &(keyinfonodeP->keyinfo));

        // Set the next pointer
        keyinfonodeP->next = NULL;

        if (err == errNone) {
            // Add this new node to the list of keyinfo's
            if (appinfo.keyinfoList == NULL) {
                appinfo.keyinfoList = keyinfonodeP;
            } else {
                insert = appinfo.keyinfoList;
                while (insert->next != NULL) {
                    insert = insert->next;
                }

                insert->next = keyinfonodeP;
            }

            redraw = true;

            goto cleanup;
        }

        MemPtrFree(keyinfonodeP);

        if (err == cpmErrUnsupported) {
            Char        *algorithmTextP;

            algorithmTextP = LstGetSelectionText(algorithmlistP, algtype);

            StrPrintF(gBuffer, "The algorithm %s is not supported by this device", algorithmTextP);
            FrmCustomAlert(ErrorAlert, gBuffer, NULL, NULL);

            goto cleanup;
        }

        if (err) {
            StrPrintF(gBuffer, "Error returned by CPMLibGenerateKey: 0x%x", err);
            FrmCustomAlert(ErrorAlert, gBuffer, NULL, NULL);

            goto cleanup;
        }

    }

cleanup:

    // Delete Form
    FrmDeleteForm(frmP);

    // Set the old form back as active
    FrmSetActiveForm(oldfrmP);

    if (redraw) {
        ShowKeysList();
    }

}

static void ReleaseKey(void)
{
    ListPtr             keylistP;
    Int16               selection;
    UInt32              counter             = 0;
    KeyInfoListType     *keyinfonodeP;
    KeyInfoListType     *previous           = NULL;
    Err                 err;

    keylistP = GetObjectPtr(MainKeysList);
    selection = LstGetSelection(keylistP);

    // Can't get no selection
    if (selection == -1) {
        return;
    }

    LstSetSelection(keylistP, - 1);
    LstDrawList(keylistP);
    keyinfonodeP = appinfo.keyinfoList;

    // Go and find the keyinfo
    while (counter != selection) {
        counter++;
        previous = keyinfonodeP;
        keyinfonodeP = keyinfonodeP->next;
    }

    // Release the key
    err = CPMLibReleaseKeyInfo(appinfo.cpmLibRef, &(keyinfonodeP->keyinfo));

    if (err) {
        StrPrintF(gBuffer, "Error during CPMLibReleaseKey: 0x%x", err);
        FrmCustomAlert(ErrorAlert, gBuffer, NULL, NULL);
    }

    // Remove the key from the list
    if (previous != NULL) {
        previous->next = keyinfonodeP->next;
    } else {
        appinfo.keyinfoList = keyinfonodeP->next;
    }

    MemPtrFree(keyinfonodeP);

    ShowKeysList();

    HideKeysButtons();
    ShowKeysButtons();
}

static void KeyMoreInfo(void)
{
    FormPtr             frmP;
    FormPtr             oldFormP;
    ListPtr             listP;
    Int16               selection;
    APKeyInfoType       *keyinfoP;
    KeyInfoListType     *keyinfonodeP;
    UInt32              counter;
    FieldPtr            fieldP;

    // Get the selection on the key list
    listP = GetObjectPtr(MainKeysList);
    selection = LstGetSelection(listP);

    counter = 0;
    keyinfonodeP = appinfo.keyinfoList;

    // Go and find the keyinfo
    while (counter != selection) {
        counter++;
        keyinfonodeP = keyinfonodeP->next;
    }

    keyinfoP = &(keyinfonodeP->keyinfo);

    // Init the key info form
    oldFormP = FrmGetActiveForm();
    frmP = FrmInitForm(KeyInfoForm);
    FrmSetActiveForm(frmP);

    // Set the number of algorithms
    fieldP = GetObjectPtr(KeyInfoTypeField);
    FldSetTextPtr(fieldP, kAlgorithmTypeString[keyinfoP->type]);

    fieldP = GetObjectPtr(KeyInfoUsageField);
    FldSetTextPtr(fieldP, kUsageTypeString[keyinfoP->usage]);

    // Show the form
    FrmDoDialog(frmP);

    // Delete the Form
    FrmDeleteForm(frmP);
    FrmSetActiveForm(oldFormP);
}

static void SelectKey(Int16 selection)
{
    // Draw the more buttons
    FrmShowObject(FrmGetActiveForm(), FrmGetObjectIndex(FrmGetActiveForm(), MainKeyMoreButton));

    switch (appinfo.currentAction) {
    case ACTION_KEYGEN:
      ShowKeysButtons();
      break;

    case ACTION_ENCRYPT:
      ShowEncryptButtons();
      break;

    case ACTION_DECRYPT:
      ShowDecryptButtons();
      break;
    }
}

static void EncryptBuffer()
{
    FormPtr                 frmP;
    APCipherInfoType        cipherinfo;
    ListPtr                 listP;
    Int16                   selection;
    APKeyInfoType           *keyinfoP;
    KeyInfoListType         *keyinfonodeP;
    UInt32                  counter;
    Err                     err;

    // Get the selection on the key list
    gEncryptedBufferSize = 256;
    frmP = FrmGetActiveForm();
    listP = GetObjectPtr(MainKeysList);
    selection = LstGetSelection(listP);

    counter = 0;
    MemSet(&cipherinfo, sizeof(APCipherInfoType), 0);
    keyinfonodeP = appinfo.keyinfoList;

    // Go and find the keyinfo
    while (counter != selection) {
        counter++;
        keyinfonodeP = keyinfonodeP->next;
    }

    keyinfoP = &(keyinfonodeP->keyinfo);

    err = CPMLibEncrypt(appinfo.cpmLibRef, keyinfoP, &cipherinfo, (UInt8 *)kEncryptBuffer, StrLen(kEncryptBuffer) + 1, gEncryptedBuffer, &gEncryptedBufferSize);

    if (err) {
        StrPrintF(gBuffer, "Error during CPMLibEncrypt call: 0x%x", err);
        FrmCustomAlert(ErrorAlert, gBuffer, NULL, NULL);

        return;
    }

    gEncrypted = true;
    FrmSetControlValue(frmP, FrmGetObjectIndex(frmP, MainEncryptedCheckbox), true);

    ShowEncryptButtons();


}

static void DecryptBuffer()
{
    FormPtr                 frmP;
    APCipherInfoType        cipherinfo;
    ListPtr                 listP;
    Int16                   selection;
    APKeyInfoType           *keyinfoP;
    KeyInfoListType         *keyinfonodeP;
    UInt32                  counter;
    Err                     err;
    FieldPtr                fieldP;

    // Get the selection on the key list
    gDecryptedBufferSize = 256;
    frmP = FrmGetActiveForm();
    listP = GetObjectPtr(MainKeysList);
    selection = LstGetSelection(listP);

    counter = 0;
    MemSet(&cipherinfo, sizeof(APCipherInfoType), 0);
    keyinfonodeP = appinfo.keyinfoList;

    // Go and find the keyinfo
    while (counter != selection) {
        counter++;
        keyinfonodeP = keyinfonodeP->next;
    }

    keyinfoP = &(keyinfonodeP->keyinfo);

    err = CPMLibDecrypt(appinfo.cpmLibRef, keyinfoP, &cipherinfo, (UInt8 *)gEncryptedBuffer, gEncryptedBufferSize, gDecryptedBuffer, &gDecryptedBufferSize);

    if (err) {
        StrPrintF(gBuffer, "Error during CPMLibDecrypt call: 0x%x", err);
        FrmCustomAlert(ErrorAlert, gBuffer, NULL, NULL);

        return;
    }

    fieldP = GetObjectPtr(MainDecryptField);
    FldSetTextPtr(fieldP, (Char *)gDecryptedBuffer);
    FldDrawField(fieldP);
}

static void ClearEncryptBuffer()
{
    FormPtr                 frmP;

    frmP = FrmGetActiveForm();
    gEncrypted = false;

    FrmSetControlValue(frmP, FrmGetObjectIndex(frmP, MainEncryptedCheckbox), false);

    switch (appinfo.currentAction) {
        case ACTION_ENCRYPT:
            HideEncryptButtons();
            ShowEncryptButtons();
            break;

        case ACTION_DECRYPT:
            HideDecryptButtons();
            ShowDecryptButtons();
            break;
    }
}

/***********************************************************************
 *
 * FUNCTION:    MainFormInit
 *
 * DESCRIPTION: This routine initializes the MainForm form.
 *
 * PARAMETERS:  frm - pointer to the MainForm form.
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void MainFormInit(FormPtr frmP)
{
    ListPtr     providerListP;
    ListPtr     actionListP;
    FieldPtr    encryptbufferFieldP;
    ControlPtr  ctlP;

    Err         err;
    UInt32      counter;
    UInt32      flags           = 0;


    // Setup the provider list
    providerListP = GetObjectPtr(MainProviderList);
    actionListP = GetObjectPtr(MainActionList);
    encryptbufferFieldP = GetObjectPtr(MainEncryptBufferField);

    FldSetTextPtr(encryptbufferFieldP, kEncryptBuffer);

    appinfo.providerIDList = (UInt32 *)MemPtrNew(sizeof(UInt32) * appinfo.numProviders);
    err = CPMLibEnumerateProviders(appinfo.cpmLibRef, appinfo.providerIDList, &appinfo.numProviders);

    // Allocate a providerinfo list of the right size
    appinfo.providerInfoList = (APProviderInfoType *)MemPtrNew(sizeof(APProviderInfoType) * (appinfo.numProviders));
    appinfo.providerStringList = (Char **)MemPtrNew(sizeof(Char *) * (appinfo.numProviders));

    for (counter = 0; counter < appinfo.numProviders; counter++) {
        err = CPMLibGetProviderInfo(appinfo.cpmLibRef, appinfo.providerIDList[counter], &(appinfo.providerInfoList[counter]));

        // Copy the strings
        appinfo.providerStringList[counter] = appinfo.providerInfoList[counter].name;

        // Copy the flags
        flags = flags | appinfo.providerInfoList[counter].flags;
    }

    // Examine the flags
    counter = 0;
    if (flags & APF_KEYGEN) {
        appinfo.actionStringList[counter] = kKeysString;
        counter++;
    }

    if (flags & APF_HASH) {
        appinfo.actionStringList[counter] = kHashString;
        counter++;
    }

    if (flags & APF_CIPHER) {
        appinfo.actionStringList[counter] = kEncryptString;
        counter++;
        appinfo.actionStringList[counter] = kDecryptString;
        counter++;
    }

    if (flags & APF_SIGN) {
        appinfo.actionStringList[counter] = kSignString;
        counter++;
    }

    if (flags & APF_VERIFY) {
        appinfo.actionStringList[counter] = kVerifyString;
        counter++;
    }

    LstSetListChoices(providerListP, appinfo.providerStringList, appinfo.numProviders);
    LstSetListChoices(actionListP, appinfo.actionStringList, counter);

    LstSetSelection(providerListP, -1);
    LstSetSelection(actionListP, -1);

    appinfo.selectedProvider = -1;

    ctlP = GetObjectPtr(MainEncryptedCheckbox);
    CtlSetEnabled(ctlP, false);
}


/***********************************************************************
 *
 * FUNCTION:    MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:  command  - menu item id
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormDoCommand(UInt16 command)
{
	Boolean handled = false;
	FormPtr frmP;

	switch (command)
		{
		case MainOptionsAboutStarterApp:
			MenuEraseStatus(0);					// Clear the menu status from the display.
			frmP = FrmInitForm (AboutForm);
			FrmDoDialog (frmP);					// Display the About Box.
			FrmDeleteForm (frmP);
			handled = true;
			break;

		}

	return handled;
}

static Boolean MainFormDoControl(UInt16 control)
{
    Boolean handled = false;
//    FormPtr frmP;

    switch (control) {

        case MainProviderMoreButton:
            ProviderMoreInfo();
            handled = true;
            break;

        case MainSetDefaultButton:
            ProviderSetDefault();
            handled = true;
            break;

        case MainKeyMoreButton:
            KeyMoreInfo();
            handled = true;
            break;

        case MainGenerateKeyButton:
            GenerateKey();
            handled = true;
            break;

        case MainReleaseKeyButton:
            ReleaseKey();
            handled = true;
            break;

        case MainEncryptButton:
            EncryptBuffer();
            handled = true;
            break;

        case MainClearEncryptBufferButton:
            ClearEncryptBuffer();
            handled = true;
            break;

        case MainDecryptButton:
            DecryptBuffer();
            handled = true;
            break;

    }

    return(handled);
}

static Boolean MainFormDoList(UInt16 list, Int16 selection)
{
    Boolean handled = false;

    switch (list) {
        case MainProviderList:
            SelectProvider(selection);
            handled = true;
            break;

        case MainActionList:
            SelectAction(selection);
            handled = true;
            break;

        case MainKeysList:
            SelectKey(selection);
            handled = true;
            break;

//        case
    }

    return(handled);
}

/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the
 *              "MainForm" of this application.
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventPtr eventP)
{
	Boolean handled = false;
	FormPtr frmP;

	switch (eventP->eType)
		{
		case menuEvent:
			return MainFormDoCommand(eventP->data.menu.itemID);

        case ctlSelectEvent:
            return MainFormDoControl(eventP->data.ctlSelect.controlID);

        case lstSelectEvent:
            return MainFormDoList(eventP->data.lstSelect.listID, eventP->data.lstSelect.selection);

		case frmOpenEvent:
			frmP = FrmGetActiveForm();
			MainFormInit( frmP);
			FrmDrawForm ( frmP);
			handled = true;
			break;

		case frmUpdateEvent:
			// To do any custom drawing here, first call FrmDrawForm(), then do your
			// drawing, and then set handled to true.
			break;

		default:
			break;

		}

	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    AppHandleEvent
 *
 * DESCRIPTION: This routine loads form resources and set the event
 *              handler for the form loaded.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean AppHandleEvent(EventPtr eventP)
{
	UInt16 formId;
	FormPtr frmP;

	if (eventP->eType == frmLoadEvent)
		{
		// Load the form resource.
		formId = eventP->data.frmLoad.formID;
		frmP = FrmInitForm(formId);
		FrmSetActiveForm(frmP);

		// Set the event handler for the form.  The handler of the currently
		// active form is called by FrmHandleEvent each time is receives an
		// event.
		switch (formId)
			{
			case MainForm:
				FrmSetEventHandler(frmP, MainFormHandleEvent);
				break;

			default:
//				ErrFatalDisplay("Invalid Form Load Event");
				break;

			}
		return true;
		}

	return false;
}


/***********************************************************************
 *
 * FUNCTION:    AppEventLoop
 *
 * DESCRIPTION: This routine is the event loop for the application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppEventLoop(void)
{
	UInt16 error;
	EventType event;

	do {
		EvtGetEvent(&event, evtWaitForever);

		if (! SysHandleEvent(&event))
			if (! MenuHandleEvent(0, &event, &error))
				if (! AppHandleEvent(&event))
					FrmDispatchEvent(&event);

	} while (event.eType != appStopEvent);
}


/***********************************************************************
 *
 * FUNCTION:     AppStart
 *
 * DESCRIPTION:  Get the current application's preferences.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err AppStart(void)
{
	StarterPreferenceType prefs;
	UInt16 prefsSize;
	Err err;

	// Read the saved preferences / saved-state information.
	prefsSize = sizeof(StarterPreferenceType);
	if (PrefGetAppPreferences(appFileCreator, appPrefID, &prefs, &prefsSize, true) !=
		noPreferenceFound)
		{
		}

    // Find the CPMLib get a reference to it
    // Open the TestLib
    appinfo.cpmLibRef = 0;
    appinfo.keyinfoList = NULL;
    appinfo.keyStringList = NULL;
    appinfo.currentAction  = (ActionEnum)0;

    err = SysLibFind("CPMLib", &appinfo.cpmLibRef);
    if (err) {
        // Load the library
        err = SysLibLoad('libr', 'cpml', &appinfo.cpmLibRef);
    }

    if (err) {
        char buffer[32];
        StrPrintF(buffer, "Missing CPMLib: 0x%x", err);
        FrmCustomAlert(ErrorAlert, buffer, NULL, NULL);
//        FrmAlert(LibMissingAlert);
    } else {
    	char buffer[32];
        err = CPMLibOpen(appinfo.cpmLibRef, &appinfo.numProviders);
        StrPrintF(buffer, "Found %u providers", appinfo.numProviders);
        FrmCustomAlert(ErrorAlert, buffer, NULL, NULL);
    }

	return(err);
}


/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Save the current state of the application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppStop(void)
{
	StarterPreferenceType prefs;

	// Write the saved preferences / saved-state information.  This data
	// will saved during a HotSync backup.
	PrefSetAppPreferences (appFileCreator, appPrefID, appPrefVersionNum,
		&prefs, sizeof (prefs), true);

	// Close all the open forms.
	FrmCloseAllForms ();

    if (appinfo.cpmLibRef != 0) {
        KeyInfoListType     *node;
        KeyInfoListType     *next;

    	// Now we're going to start releasing memory that we allocated
	    if (appinfo.numProviders > 0) {

	        MemPtrFree(appinfo.providerStringList);
	        MemPtrFree(appinfo.providerInfoList);
	        MemPtrFree(appinfo.providerIDList);

    	}

    	if (appinfo.keyStringList != NULL) {
    	    UInt32      counter;

    	    for (counter = 0; counter < appinfo.keyStringSize; counter++) {
    	        MemPtrFree(appinfo.keyStringList[counter]);
    	    }

    	    MemPtrFree(appinfo.keyStringList);

    	    appinfo.keyStringList = NULL;
    	    appinfo.keyStringSize = 0;
    	}

        node = appinfo.keyinfoList;
        while (node != NULL) {

            CPMLibReleaseKeyInfo(appinfo.cpmLibRef, &node->keyinfo);

            next = node->next;
            MemPtrFree(node);
            node = next;
        }

        appinfo.keyinfoList = NULL;

        CPMLibClose(appinfo.cpmLibRef);
	    SysLibRemove(appinfo.cpmLibRef);

	}

}


/***********************************************************************
 *
 * FUNCTION:    StarterPalmMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code.
 *              cmdPB - pointer to a structure that is associated with the launch code.
 *              launchFlags -  word value providing extra information about the launch.
 *
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static UInt32 StarterPalmMain(UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	Err error;

	error = RomVersionCompatible (ourMinVersion, launchFlags);
	if (error) return (error);

	switch (cmd)
		{
		case sysAppLaunchCmdNormalLaunch:
			error = AppStart();
			if (error)
				return error;

			FrmGotoForm(MainForm);
			AppEventLoop();
			AppStop();
			break;

		default:
			break;

		}

	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code.
 *              cmdPB - pointer to a structure that is associated with the launch code.
 *              launchFlags -  word value providing extra information about the launch.
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
UInt32 PilotMain( UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	return StarterPalmMain(cmd, cmdPBP, launchFlags);
}
