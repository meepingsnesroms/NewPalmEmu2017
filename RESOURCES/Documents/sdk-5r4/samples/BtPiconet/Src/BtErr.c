/******************************************************************************
 *
 * Copyright (c) 1994-2002 PalmSource, Inc. All rights reserved.
 *
 * File: BtErr.c
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 * 	Converts Bluetooth errno to a string
 *
 *****************************************************************************/

#include <PalmOS.h>
#include "BtLib.h"
#include "BtLibTypes.h"


Char *ConvertBtErrToString(Err errno);


Char *ConvertBtErrToString(Err errno)
{
	Char *msg;
	
	switch (errno)
	{
		case btLibErrNoError:
			msg = (Char *) "btLibErrNoError";
			break;
			
		case btLibErrError:
			msg = (Char *) "ErrError";
			break;
			
		case btLibErrNotOpen:
			msg = (Char *) "ErrNotOpen";
			break;
			
		case btLibErrBluetoothOff:
			msg = (Char *) "ErrBluetoothOff";
			break;
			
		case btLibErrNoPrefs:
			msg = (Char *) "ErrNoPrefs";
			break;
			
		case btLibErrAlreadyOpen:
			msg = (Char *) "ErrAlreadyOpen";
			break;
			
		case btLibErrOutOfMemory:
			msg = (Char *) "ErrOutOfMemory";
			break;
			
		case btLibErrFailed:
			msg = (Char *) "ErrFailed";
			break;
			
		case btLibErrInProgress:
			msg = (Char *) "ErrInProgress";
			break;
			
		case btLibErrParamError:
			msg = (Char *) "ErrParamError";
			break;
			
		case btLibErrTooMany:
			msg = (Char *) "ErrTooMany";
			break;
			
		case btLibErrPending:
			msg = (Char *) "ErrPending";
			break;
			
		case btLibErrNotInProgress:
			msg = (Char *) "ErrNotInProgress";
			break;
			
		case btLibErrRadioInitFailed:
			msg = (Char *) "ErrRadioInitFailed";
			break;
			
		case btLibErrRadioFatal:
			msg = (Char *) "ErrRadioFatal";
			break;
			
		case btLibErrRadioInitialized:
			msg = (Char *) "ErrRadioInitialized";
			break;
			
		case btLibErrRadioSleepWake:
			msg = (Char *) "ErrRadioSleepWake";
			break;
			
		case btLibErrNoConnection:
			msg = (Char *) "ErrNoConnection";
			break;
			
		case btLibErrAlreadyRegistered:
			msg = (Char *) "ErrAlreadyRegistered";
			break;
			
		case btLibErrNoAclLink:
			msg = (Char *) "ErrNoAclLink";
			break;
			
		case btLibErrSdpRemoteRecord:
			msg = (Char *) "ErrSdpRemoteRecord";
			break;
			
		case btLibErrSdpAdvertised:
			msg = (Char *) "ErrSdpAdvertised";
			break;
			
		case btLibErrSdpFormat:
			msg = (Char *) "ErrSdpFormat";
			break;
			
		case btLibErrSdpNotAdvertised:
			msg = (Char *) "ErrSdpNotAdvertised";
			break;
			
		case btLibErrSdpQueryVersion:
			msg = (Char *) "ErrSdpQueryVersion";
			break;
			
		case btLibErrSdpQueryHandle:
			msg = (Char *) "ErrSdpQueryHandle";
			break;
			
		case btLibErrSdpQuerySyntax:
			msg = (Char *) "ErrSdpQuerySyntax";
			break;
			
		case btLibErrSdpQueryPduSize:
			msg = (Char *) "ErrSdpQueryPduSize";
			break;
			
		case btLibErrSdpQueryContinuation:
			msg = (Char *) "ErrSdpQueryContinuation";
			break;
			
		case btLibErrSdpQueryResources:
			msg = (Char *) "ErrSdpQueryResources";
			break;
			
		case btLibErrSdpQueryDisconnect:
			msg = (Char *) "ErrSdpQueryDisconnect";
			break;
			
		case btLibErrSdpInvalidResponse:
			msg = (Char *) "ErrSdpInvalidResponse";
			break;
			
		case btLibErrSdpAttributeNotSet:
			msg = (Char *) "ErrSdpAttributeNotSet";
			break;
			
		case btLibErrSdpMapped:
			msg = (Char *) "ErrSdpMapped";
			break;
			
		case btLibErrSocket:
			msg = (Char *) "ErrSocket";
			break;
			
		case btLibErrSocketProtocol:
			msg = (Char *) "ErrSocketProtocol";
			break;
			
		case btLibErrSocketRole:
			msg = (Char *) "ErrSocketRole";
			break;
			
		case btLibErrSocketPsmUnavailable:
			msg = (Char *) "ErrSocketPsmUnavailable";
			break;
			
		case btLibErrSocketChannelUnavailable:
			msg = (Char *) "ErrSocketChannelUnavailable";
			break;
			
		case btLibErrSocketUserDisconnect:
			msg = (Char *) "ErrSocketUserDisconnect";
			break;
			
		case btLibErrCanceled:
			msg = (Char *) "ErrCanceled";
			break;
			
		case btLibErrBusy:
			msg = (Char *) "ErrBusy";
			break;
			
		case btLibMeStatusUnknownHciCommand:
			msg = (Char *) "MeStatusUnknownHciCommand";
			break;
			
		case btLibMeStatusNoConnection:
			msg = (Char *) "MeStatusNoConnection";
			break;
			
		case btLibMeStatusHardwareFailure:		
			msg = (Char *) "MeStatusHardwareFailure";
			break;
			
		case btLibMeStatusPageTimeout:
			msg = (Char *) "MeStatusPageTimeout";
			break;
			
		case btLibMeStatusAuthenticateFailure:
			msg = (Char *) "MeStatusAuthenticateFailure";
			break;
			
		case btLibMeStatusMissingKey:
			msg = (Char *) "MeStatusMissingKey";
			break;
			
		case btLibMeStatusMemoryFull:
			msg = (Char *) "MeStatusMemoryFull";
			break;
			
		case btLibMeStatusConnnectionTimeout:
			msg = (Char *) "MeStatusConnnectionTimeout";
			break;
			
		case btLibMeStatusMaxConnections:
			msg = (Char *) "MeStatusMaxConnections";
			break;
			
		case btLibMeStatusMaxScoConnections:
			msg = (Char *) "MeStatusMaxScoConnections";
			break;
			
		case btLibMeStatusMaxAclConnections:
			msg = (Char *) "MeStatusMaxAclConnections";
			break;
			
		case btLibMeStatusCommandDisallowed:
			msg = (Char *) "MeStatusCommandDisallowed";
			break;
			
		case btLibMeStatusLimitedResources:
			msg = (Char *) "MeStatusLimitedResources";
			break;
			
		case btLibMeStatusSecurityError:
			msg = (Char *) "MeStatusSecurityError";
			break;
			
		case btLibMeStatusPersonalDevice:
			msg = (Char *) "MeStatusPersonalDevice";
			break;
			
		case btLibMeStatusHostTimeout:
			msg = (Char *) "MeStatusHostTimeout";
			break;
			
		case btLibMeStatusUnsupportedFeature:
			msg = (Char *) "MeStatusUnsupportedFeature";
			break;
			
		case btLibMeStatusInvalidHciParam:
			msg = (Char *) "MeStatusInvalidHciParam";
			break;
			
		case btLibMeStatusUserTerminated:
			msg = (Char *) "MeStatusUserTerminated";
			break;
			
		case btLibMeStatusLowResources:
			msg = (Char *) "MeStatusLowResources";
			break;
			
		case btLibMeStatusPowerOff:
			msg = (Char *) "MeStatusPowerOff";
			break;
			
		case btLibMeStatusLocalTerminated:
			msg = (Char *) "MeStatusLocalTerminated";
			break;
			
		case btLibMeStatusRepeatedAttempts:
			msg = (Char *) "MeStatusRepeatedAttempts";
			break;
			
		case btLibMeStatusPairingNotAllowed:
			msg = (Char *) "MeStatusPairingNotAllowed";
			break;
			
		case btLibMeStatusUnknownLmpPDU:
			msg = (Char *) "MeStatusUnknownLmpPDU";
			break;
			
		case btLibMeStatusUnsupportedRemote:
			msg = (Char *) "MeStatusUnsupportedRemote";
			break;
			
		case btLibMeStatusScoOffsetRejected:
			msg = (Char *) "MeStatusScoOffsetRejected";
			break;
			
		case btLibMeStatusScoIntervalRejected:
			msg = (Char *) "MeStatusScoIntervalRejected";
			break;
			
		case btLibMeStatusScoAirModeRejected:
			msg = (Char *) "MeStatusScoAirModeRejected";
			break;
			
		case btLibMeStatusInvalidLmpParam:
			msg = (Char *) "MeStatusInvalidLmpParam";
			break;
			
		case btLibMeStatusUnspecifiedError:
			msg = (Char *) "MeStatusUnspecifiedError";
			break;
			
		case btLibMeStatusUnsupportedLmpParam:
			msg = (Char *) "MeStatusUnsupportedLmpParam";
			break;
			
		case btLibMeStatusRoleChangeNotAllowed:
			msg = (Char *) "MeStatusRoleChangeNotAllowed";
			break;
			
		case btLibMeStatusLmpResponseTimeout:
			msg = (Char *) "MeStatusLmpResponseTimeout";
			break;
			
		case btLibMeStatusLmpTransdCollision:
			msg = (Char *) "MeStatusLmpTransdCollision";
			break;
			
		case btLibMeStatusLmpPduNotAllowed:
			msg = (Char *) "MeStatusLmpPduNotAllowed";
			break;
			
		case btLibL2DiscReasonUnknown:
			msg = (Char *) "L2DiscReasonUnknown";
			break;
			
		case btLibL2DiscUserRequest:
			msg = (Char *) "L2DiscUserRequest";
			break;
			
		case btLibL2DiscRequestTimeout:
			msg = (Char *) "L2DiscRequestTimeout";
			break;
			
		case btLibL2DiscLinkDisc:
			msg = (Char *) "L2DiscLinkDisc";
			break;
			
		case btLibL2DiscQosViolation:
			msg = (Char *) "L2DiscQosViolation";
			break;
			
		case btLibL2DiscSecurityBlock:
			msg = (Char *) "L2DiscSecurityBlock";
			break;
			
		case btLibL2DiscConnPsmUnsupported:
			msg = (Char *) "L2DiscConnPsmUnsupported";
			break;
			
		case btLibL2DiscConnSecurityBlock:
			msg = (Char *) "L2DiscConnSecurityBlock";
			break;
			
		case btLibL2DiscConnNoResources:
			msg = (Char *) "L2DiscConnNoResources";
			break;
			
		case btLibL2DiscConfigUnacceptable:
			msg = (Char *) "L2DiscConfigUnacceptable";
			break;
			
		case btLibL2DiscConfigReject:
			msg = (Char *) "L2DiscConfigReject";
			break;
			
		case btLibL2DiscConfigOptions:
			msg = (Char *) "L2DiscConfigOptions";
			break;
			
		case btLibServiceShutdownAppUse:
			msg = (Char *) "ServiceShutdownAppUse";
			break;
			
		case btLibServiceShutdownPowerCycled:
			msg = (Char *) "ServiceShutdownPowerCycled";
			break;
			
		case btLibServiceShutdownAclDrop:
			msg = (Char *) "ServiceShutdownAclDrop";
			break;
			
		case btLibServiceShutdownTimeout:
			msg = (Char *) "ServiceShutdownTimeout";
			break;
			
		case btLibServiceShutdownDetached:
			msg = (Char *) "ServiceShutdownDetached";
			break;
			
		case btLibErrInUseByService:
			msg = (Char *) "ErrInUseByService";
			break;

		case btLibErrNoPiconet:
			msg = (Char *) "ErrNoPiconet";
			break;
			
		case btLibErrRoleChange:
			msg = (Char *) "ErrRoleChange";
			break;
						
		case btLibNotYetSupported:
			msg = (Char *) "NotYetSupported";
			break;
			
		case btLibErrSdpNotMapped:
			msg = (Char *) "ErrSdpNotMapped";
			break;
			
		case btLibErrAlreadyConnected:
			msg = (Char *) "ErrAlreadyConnected";
			break;
			
		default:
			msg = (Char *) "Unknown BT error";
			break;
	}
	
	return (msg);
}
