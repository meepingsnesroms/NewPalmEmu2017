#ifndef ASTROLOGY
#define ASTROLOGY

/* this gives the selector base for tapwave interface */
#define trapTwSelectorBase              256

/* selector numbers for 68K calls */
#define trapTwDeviceOpen                256
#define trapTwDeviceClose               257
#define trapTwDeviceRead                258
#define trapTwDeviceWrite               259
#define trapTwDeviceGetProperty         260
#define trapTwDeviceSetProperty         261
#define trapTwDeviceControl             262

#define trapTwGetHoldState              263
#define trapTwSetHoldState              264

#define trapTwHighScoreRegister         265
#define trapTwHighScoreUnregister       266
#define trapTwHighScoreReport           267
#define trapTwHighScoreGetSummary       268
#define trapTwHighScoreGetDetails       269

#define trapTwInputOpen                 270
#define trapTwInputClose                271
#define trapTwInputActivate             272
#define trapTwInputDeactivate           273
#define trapTwInputGetPeriod            274
#define trapTwInputSetPeriod            275
#define trapTwInputGetCapacity          276
#define trapTwInputSetCapacity          277
#define trapTwInputGetFormat            278
#define trapTwInputSetFormat            279
#define trapTwInputPeek                 280
#define trapTwInputRead                 281
#define trapTwInputPoll                 282
#define trapTwInputControl              283

#define trapTwNavResetCalibration       284
#define trapTwNavCalibrate              285

#define trapTwSndPlaySystemSound        286
#define trapTwSndGetVolume              287
#define trapTwSndSetMute                288
#define trapTwSndSetVolume              289
#define trapTwSndSetBassBoost           290
#define trapTwSndGetMute                291
#define trapTwSndGetBassBoost           292

#define trapTwCtlSetFrameStyle          293
#define trapWinGetBitmapDimensions      294
#define trapTwOSReserved1               295
#define trapTwOSReserved2               296
#define trapTwOSReserved3               297
#define trapTwOSReserved4               298
#define trapTwConvert68KBitmapToNative  299

#define trapTwDrawTitleBar              300
#define trapTwSetTapwaveScrollBar       301
#define trapTwGetSlotNumberForVolume    302

#define trapTwGfxOpen                   303
#define trapTwGfxClose                  304
#define trapTwGfxGetInfo                305
#define trapTwGfxGetMemoryUsage         306
#define trapTwGfxGetDisplaySurface      307
#define trapTwGfxGetPalmDisplaySurface  308
#define trapTwGfxInVBlank               309
#define trapTwGfxWaitForVBlank          310
#define trapTwGfxAllocSurface           311
#define trapTwGfxFreeSurface            312
#define trapTwGfxSetClip                313
#define trapTwGfxGetClip                314
#define trapTwGfxGetSurfaceInfo         315
#define trapTwGfxLockSurface            316
#define trapTwGfxUnlockSurface          317
#define trapTwGfxReadSurface            318
#define trapTwGfxWriteSurface           319
#define trapTwGfxIsSurfaceReady         320
#define trapTwGfxBitBlt                 321
#define trapTwGfxStretchBlt             322
#define trapTwGfxTransformBlt           323
#define trapTwGfxDrawPoints             324
#define trapTwGfxDrawColorPoints        325
#define trapTwGfxDrawLines              326
#define trapTwGfxDrawLineSegments       327
#define trapTwGfxDrawRect               328
#define trapTwGfxFillRect               329
#define trapTwGfxDrawSpans              330
#define trapTwGfxDrawBitmap             331
#define trapTwGfxReadSurfaceRegion      332
#define trapTwGfxWriteSurfaceRegion     333
#define trapTwGfxBlendBlt               334
#define trapTwGfxTileBlt                335
#define trapTwGfxMaskBlt                336
#define trapTwGfxAsyncBlt               337
#define trapTwGfxMaskBlendBlt           338
#define trapTwGfxTransparentBlt         339
#define trapTwGfxStretchBlt2            340
#define trapTwGfxReserved4              341
#define trapTwGfxReserved5              342
#define trapTwGfxReserved6              343
#define trapTwGfxReserved7              344
#define trapTwGfxReserved8              345
#define trapTwGfxReserved9              346
#define trapTwGfxReserved10             347
#define trapTwGfxReserved11             348
#define trapTwGfxReserved12             349
#define trapTwGfxReserved13             350
#define trapTwGfxReserved14             351
#define trapTwGfxReserved15             352
#define trapTwGfxReserved16             353
#define trapTwGfxReserved17             354
#define trapTwGfxReserved18             355
#define trapTwGfxReserved19             356
#define trapTwGfxDrawPalmBitmap         357

#define trapTwSecGetFunctions           358
#define trapTwSecReserved1              359
#define trapTwSecReserved2              360
#define trapTwSecReserved3              361
#define trapTwSecReserved4              362
#define trapTwSecReserved5              363
#define trapTwSecReserved6              364
#define trapTwSecReserved7              365
#define trapTwSecReserved8              366
#define trapTwSecReserved9              367
#define trapTwSecReserved10             368
#define trapTwSecReserved11             369
#define trapTwSecReserved12             370
#define trapTwSecReserved13             371
#define trapTwSecReserved14             372
#define trapTwSecReserved15             373
#define trapTwSecReserved16             374

#define trapTwCreateDatabaseFromImage   375
#define trapTwGetGraphicForButton       376
#define trapTwHighScoreGetTournament    377
#define trapTwBlendMask                 378
#define trapTwGetPRCDataDirectory       379
#define trapTwGetDBDataDirectory        380
#define trapTwGetSlotRefNumForSlot      381
#define trapTwGetMicroSeconds           382
#define trapTwPickColor                 383
#define trapTwAdjustColor               384
#define trapTwMenuIsVisible             385
#define trapTwBatteryState              386

#define trapTwFindModule                387
#define trapTwLoadModule                388
#define trapTwUnloadModule              389
#define trapTwConfirmQuit               390
#define trapTwTintBitmap                391
#define trapTwSetCompatibleKeys         392

/*
 * TwJpg Traps
 */
#define trapTwJpgOpenImage                              393
#define trapTwJpgCloseImage                             394
#define trapTwJpgGetImageInfo                           395
#define trapTwJpgSetAbortCheck                          396
#define trapTwJpgGetAbortCheck                          397
#define trapTwJpgDecodeImage                            398
#define trapTwJpgDecodeAndScaleImage                    399
#define trapTwJpgDecodeImageToSurface                   400
#define trapTwJpgDecodeImageToNewSurface                401
#define trapTwJpgScaleImageBuffer                       402
#define trapTwJpgReserved0                              403
#define trapTwJpgReserved1                              404
#define trapTwJpgReserved2                              405
#define trapTwJpgReserved3                              406
#define trapTwJpgReserved4                              407
#define trapTwJpgReserved5                              408
#define trapTwJpgReserved6                              409
#define trapTwJpgReserved7                              410
#define trapTwJpgReserved8                              411
#define trapTwJpgReserved9                              412

#define trapTwCreateAppBackground       413
#define trapTwSndSetAlarmPlaying        414
#define trapTwSndSetMusicControlState   415

#define trapTwMpOpen					416
#define trapTwMpClose					417
#define trapTwMpHostGame		        418
#define trapTwMpHostInvitePlayer        419
#define trapTwMpHostDisinvitePlayer	    420
#define trapTwMpHostStartGame		    421
#define trapTwMpGuestAcceptInvitation   422
#define trapTwMpCancelGame				423
#define trapTwMpGetPlayerInfo			424
#define trapTwMpGetNumPlayers			425
#define trapTwMpGetAllPlayers		    426
#define trapTwMpGetNumAcceptedPlayers	427
#define trapTwMpGetAcceptedPlayers	    428
#define trapTwMpReserved0               429
#define trapTwMpReserved1               430
#define trapTwMpReserved2               431
#define trapTwMpReserved3               432
#define trapTwMpReserved4               433
#define trapTwMpReserved5               434
#define trapTwMpReserved6               435
#define trapTwMpReserved7               436
#define trapTwMpReserved8               437
#define trapTwMpReserved9               438

#define trapTwSmfOpen                   439
#define trapTwSmfClose                  440
#define trapTwSmfPlay                   441
#define trapTwSmfIsPlaying              442
#define trapTwSmfStop                   443
#define trapTwMidiOpen                  444
#define trapTwMidiClose                 445
#define trapTwMidiNoteOn                446
#define trapTwMidiNoteOff               447
#define trapTwMidiProgramChange         448
#define trapTwMidiPitchBend             449
#define trapTwMidiSysEx                 450
#define trapTwMidiGetLimits             451
#define trapTwMidiControlChange         452
#define trapTwMidiSetMasterVolume       453
#define trapTwMidiGetMasterVolume       454
#define trapTwMidiPlaySmf               455
#define trapTwMidiReserved2             456
#define trapTwMidiReserved3             457
#define trapTwMidiReserved4             458
#define trapTwMidiReserved5             459
#define trapTwMidiReserved6             460
#define trapTwHALSoundNumActiveStreams  461


void tapwavedispatch();
#endif // ASTROLOGY

