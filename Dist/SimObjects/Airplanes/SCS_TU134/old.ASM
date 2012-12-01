; Automatic generated AIR file

		include asm.inc			; include this in ALL .asm files!
		include airtoken.inc	; definitions of token macros
		include sim1.inc		; definitions of token values

.data

sim_data			label   byte

;********************************************************************************************************************


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_TITLE		; 1h
DATA_LENGTH_001		DD	18
UNKNOWN_DATA_001	DB 054H, 075H, 070H, 06fH, 06cH, 065H, 076H, 020H
					DB 054H, 075H, 02dH, 031H, 033H, 034H, 041H, 02dH
					DB 033H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_DESCRIPTION		; 2h
DATA_LENGTH_002		DD	21
UNKNOWN_DATA_002	DB 054H, 075H, 02dH, 031H, 033H, 034H, 041H, 02dH
					DB 033H, 020H, 066H, 06fH, 072H, 020H, 046H, 053H
					DB 032H, 030H, 030H, 034H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_PERFORMANCE		; 3h
DATA_LENGTH_003		DD	114
UNKNOWN_DATA_003	DB 043H, 072H, 075H, 069H, 073H, 065H, 020H, 053H
					DB 070H, 065H, 065H, 064H, 009H, 02eH, 038H, 032H
					DB 020H, 04dH, 061H, 063H, 068H, 00dH, 00aH, 04dH
					DB 061H, 078H, 069H, 06dH, 075H, 06dH, 020H, 052H
					DB 061H, 06eH, 067H, 065H, 009H, 032H, 020H, 034H
					DB 030H, 030H, 020H, 06bH, 06dH, 00dH, 00aH, 053H
					DB 065H, 072H, 076H, 069H, 063H, 065H, 020H, 043H
					DB 065H, 069H, 06cH, 069H, 06eH, 067H, 009H, 031H
					DB 031H, 020H, 036H, 030H, 030H, 020H, 06dH, 00dH
					DB 00aH, 04dH, 061H, 078H, 020H, 054H, 061H, 06bH
					DB 065H, 06fH, 066H, 066H, 020H, 057H, 065H, 069H
					DB 067H, 068H, 074H, 009H, 034H, 039H, 020H, 030H
					DB 030H, 030H, 00dH, 00aH, 053H, 065H, 061H, 074H
					DB 069H, 06eH, 067H, 009H, 009H, 037H, 036H, 00dH
					DB 00aH, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_TAIL_NUMBER		; 4h
DATA_LENGTH_004		DD	9
UNKNOWN_DATA_004	DB 052H, 041H, 02dH, 036H, 035H, 037H, 037H, 035H
					DB 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_SIM_NAME		; 100h
DATA_LENGTH_005		DD	5
UNKNOWN_DATA_005	DB 073H, 069H, 06dH, 031H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_NORMAL_MDL_NAME		; 101h
DATA_LENGTH_006		DD	8
UNKNOWN_DATA_006	DB 074H, 075H, 02dH, 031H, 033H, 034H, 041H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_PANEL_NAME		; 104h
DATA_LENGTH_007		DD	10
UNKNOWN_DATA_007	DB 054H, 075H, 02dH, 031H, 033H, 034H, 041H, 02dH
					DB 033H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_AC_CATEGORY		; 105h
DATA_LENGTH_008		DD	4
UNKNOWN_DATA_008	DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_CONTROL_RESPONSE		; 300h
DATA_LENGTH_009		DD	12
UNKNOWN_DATA_009	DB 096H, 000H, 0faH, 000H, 096H, 000H, 0faH, 000H
					DB 096H, 000H, 0faH, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_ENGINE_TYPE		; 310h
DATA_LENGTH_010		DD	1
UNKNOWN_DATA_010	DB 001H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_NUMBER_ENGINES		; 311h
DATA_LENGTH_011		DD	2
UNKNOWN_DATA_011	DB 002H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_FUEL_WEIGHT		; 312h
DATA_LENGTH_012		DD	2
UNKNOWN_DATA_012	DB 09aH, 006H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_THROTTLE_LIMIT		; 313h
DATA_LENGTH_013		DD	2
UNKNOWN_DATA_013	DB 000H, 0e0H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_LANDME_AVAIL		; 314h
DATA_LENGTH_014		DD	2
UNKNOWN_DATA_014	DB 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_FLAPS_DETENTS		; 315h
DATA_LENGTH_015		DD	2
UNKNOWN_DATA_015	DB 004H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_MAX_OPERATING_MACH		; 316h
DATA_LENGTH_016		DD	4
UNKNOWN_DATA_016	DB 099H, 041H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_AUTOPILOT_AVAIL		; 317h
DATA_LENGTH_017		DD	16
UNKNOWN_DATA_017	DB 001H, 000H, 000H, 000H, 001H, 000H, 000H, 000H
					DB 000H, 000H, 064H, 000H, 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_FLAPS_AVAIL		; 318h
DATA_LENGTH_018		DD	4
UNKNOWN_DATA_018	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_STALL_HORN_AVAIL		; 319h
DATA_LENGTH_019		DD	4
UNKNOWN_DATA_019	DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_CONTROLS_CONSTANTS		; 320h
DATA_LENGTH_020		DD	140
UNKNOWN_DATA_020	DB 000H, 000H, 000H, 000H, 000H, 040H, 051H, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 05aH, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 04fH, 040H
					DB 0f6H, 028H, 05cH, 08fH, 0c2H, 0f5H, 0d8H, 03fH
					DB 0ecH, 051H, 0b8H, 01eH, 085H, 0ebH, 0d1H, 03fH
					DB 01fH, 085H, 0ebH, 051H, 0b8H, 01eH, 0d5H, 03fH
					DB 01fH, 085H, 0ebH, 051H, 0b8H, 01eH, 0d5H, 03fH
					DB 029H, 05cH, 08fH, 0c2H, 0f5H, 028H, 0dcH, 03fH
					DB 0faH, 07eH, 06aH, 0bcH, 074H, 093H, 0b8H, 03fH
					DB 001H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 08fH, 0c2H, 0f5H, 028H
					DB 05cH, 08fH, 0e2H, 03fH, 0cdH, 0ccH, 0ccH, 0ccH
					DB 0ccH, 0ccH, 0dcH, 0bfH, 000H, 000H, 000H, 000H
					DB 000H, 000H, 010H, 040H, 09aH, 099H, 099H, 099H
					DB 099H, 099H, 0d9H, 0bfH, 000H, 000H, 000H, 000H
					DB 000H, 000H, 022H, 0c0H, 0a7H, 0e8H, 048H, 02eH
					DB 0ffH, 021H, 0e9H, 03fH, 07aH, 000H, 08bH, 0fcH
					DB 0faH, 021H, 0e9H, 03fH
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_ENG_MIXTURE_AVAIL		; 322h
DATA_LENGTH_021		DD	4
UNKNOWN_DATA_021	DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_CARB_HEAT_AVAIL		; 323h
DATA_LENGTH_022		DD	4
UNKNOWN_DATA_022	DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_PITOT_HEAT_AVAIL		; 324h
DATA_LENGTH_023		DD	4
UNKNOWN_DATA_023	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_GEAR_WARNING_HORN		; 325h
DATA_LENGTH_024		DD	24
UNKNOWN_DATA_024	DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_SPOILER_AVAIL		; 327h
DATA_LENGTH_025		DD	4
UNKNOWN_DATA_025	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_IS_TAIL_DRAGGER		; 328h
DATA_LENGTH_026		DD	4
UNKNOWN_DATA_026	DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_AUTO_THROTTLE		; 329h
DATA_LENGTH_027		DD	12
UNKNOWN_DATA_027	DB 001H, 000H, 000H, 000H, 001H, 000H, 000H, 000H
					DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_PROP_TYPE_AVAIL		; 330h
DATA_LENGTH_028		DD	4
UNKNOWN_DATA_028	DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_STROBES_AVAIL		; 331h
DATA_LENGTH_029		DD	4
UNKNOWN_DATA_029	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_TOE_BRAKES_AVAIL		; 332h
DATA_LENGTH_030		DD	4
UNKNOWN_DATA_030	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_NAV_OBS_AVAIL		; 333h
DATA_LENGTH_031		DD	8
UNKNOWN_DATA_031	DB 001H, 000H, 000H, 000H, 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_VOR2_GAUGE_AVAIL		; 334h
DATA_LENGTH_032		DD	4
UNKNOWN_DATA_032	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_NAV_RADIOS_AVAIL		; 335h
DATA_LENGTH_033		DD	12
UNKNOWN_DATA_033	DB 001H, 000H, 000H, 000H, 001H, 000H, 000H, 000H
					DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_AUTO_SPOILER_AVAIL		; 337h
DATA_LENGTH_034		DD	4
UNKNOWN_DATA_034	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_AUTO_BRAKES_AVAIL		; 338h
DATA_LENGTH_035		DD	4
UNKNOWN_DATA_035	DB 001H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_STICK_SHAKER		; 339h
DATA_LENGTH_036		DD	8
UNKNOWN_DATA_036	DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_SPOILERONS		; 340h
DATA_LENGTH_037		DD	28
UNKNOWN_DATA_037	DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 012H, 083H, 0c0H, 0caH
					DB 0a1H, 045H, 0c6H, 03fH, 000H, 000H, 000H, 000H
					DB 000H, 000H, 008H, 040H
TOKEN_END


; Token 341h - Elevator effectiveness scaling table (max 7 entries)
; IN:  Elevator angle  (radians)
; OUT: Effectiveness scalar
TOKEN_BEGIN AIR_ELEVATOR_SCALING
	dd	7		; Number of Entries
	REAL8	-0.506100,	1.000000
	REAL8	-0.209000,	1.000000
	REAL8	-0.122000,	1.000000
	REAL8	0.000000,	1.000000
	REAL8	0.279000,	1.000000
	REAL8	0.349000,	0.900000
	REAL8	0.506100,	0.400000
TOKEN_END


; Token 342h - Aileron effectiveness scaling table (max 7 entries)
; IN:  Aileron angle  (radians)
; OUT: Effectiveness scalar
TOKEN_BEGIN AIR_AILERON_SCALING
	dd	7		; Number of Entries
	REAL8	-0.349000,	0.960000
	REAL8	-0.261000,	0.810000
	REAL8	-0.175000,	0.750000
	REAL8	0.000000,	0.710000
	REAL8	0.175000,	0.750000
	REAL8	0.261000,	0.810000
	REAL8	0.349000,	0.960000
TOKEN_END


; Token 343h - Rudder effectiveness scaling table (max 7 entries)
; IN:  Rudder angle  (radians)
; OUT: Effectiveness scalar
TOKEN_BEGIN AIR_RUDDER_SCALING
	dd	7		; Number of Entries
	REAL8	-0.785000,	0.500000
	REAL8	-0.524000,	0.600000
	REAL8	-0.175000,	0.900000
	REAL8	0.000000,	1.000000
	REAL8	0.175000,	0.900000
	REAL8	0.524000,	0.600000
	REAL8	0.785000,	0.500000
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_SMOKE_AVAIL		; 344h
DATA_LENGTH_038		DD	4
UNKNOWN_DATA_038	DB 001H, 000H, 000H, 000H
TOKEN_END


; Token 400h - Ground effect
;Scalar on Lift due to ground proximity  (max 11 entries)
;IN:  Ratio of wingspan / height above ground
;OUT: Scalar on CL
TOKEN_BEGIN AIR_GROUND_EFFECT
	dd	11		; Number of Entries
	REAL8	0.054000,	1.184000
	REAL8	0.100000,	1.131000
	REAL8	0.200000,	1.070000
	REAL8	0.300000,	1.032000
	REAL8	0.400000,	1.011000
	REAL8	0.500000,	1.003000
	REAL8	0.600000,	1.000900
	REAL8	0.700000,	1.000600
	REAL8	0.800000,	1.000300
	REAL8	0.900000,	1.000100
	REAL8	1.000000,	1.000000
TOKEN_END


; Token 401h - Scalar on Lift due to mach (max 17 entries)
; IN:  Mach
; OUT: Scalar on CL0
TOKEN_BEGIN AIR_CL_MACH
	dd	17		; Number of Entries
	REAL8	0.000000,	1.000000
	REAL8	0.200000,	1.011900
	REAL8	0.400000,	1.031700
	REAL8	0.600000,	1.091300
	REAL8	0.800000,	1.269800
	REAL8	1.000000,	1.388900
	REAL8	1.200000,	0.992100
	REAL8	1.400000,	0.754000
	REAL8	1.600000,	0.595200
	REAL8	1.800000,	0.535700
	REAL8	2.000000,	0.456400
	REAL8	2.200000,	0.396800
	REAL8	2.400000,	0.357100
	REAL8	2.600000,	0.337300
	REAL8	2.800000,	0.327400
	REAL8	3.000000,	0.327400
	REAL8	3.200000,	0.327400
TOKEN_END


; Token 404h - CL vs. Alpha
;The first entry defines the number of data points (maximum 47 entries)
TOKEN_BEGIN AIR_CL_ALPHA
	dd	24		; Number of Entries
	REAL8	-3.141590,	0.000000
	REAL8	-2.748890,	0.359860
	REAL8	-2.356190,	0.500000
	REAL8	-1.963490,	0.359860
	REAL8	-1.570790,	0.000000
	REAL8	-1.047200,	-0.600000
	REAL8	-0.698130,	-1.300000
	REAL8	-0.349000,	-1.236000
	REAL8	-0.052300,	-0.190000
	REAL8	-0.016900,	0.000000
	REAL8	0.000000,	0.100000
	REAL8	0.123000,	0.820000
	REAL8	0.182000,	1.120000
	REAL8	0.230000,	1.284000
	REAL8	0.251000,	1.310000
	REAL8	0.271000,	1.290000
	REAL8	0.291000,	1.240000
	REAL8	0.302000,	1.210000
	REAL8	0.330000,	1.240000
	REAL8	0.349000,	1.100000
	REAL8	0.471000,	0.368900
	REAL8	0.698130,	0.109400
	REAL8	1.963490,	-0.559860
	REAL8	3.141580,	0.000000
TOKEN_END


; Token 410h - Integer mach table on Clde (fixed 17 elements)
; IN: Mach index
; OUT: Delta Clde due to mach
TOKEN_BEGIN AIR_CL_DELTAE
	dw	0			; 0.0
	dw	0			; 0.2
	dw	-21			; 0.4
	dw	-82			; 0.6
	dw	-246			; 0.8
	dw	-246			; 1.0
	dw	-205			; 1.2
	dw	-164			; 1.4
	dw	-123			; 1.6
	dw	-82			; 1.8
	dw	-41			; 2.0
	dw	-41			; 2.2
	dw	-41			; 2.4
	dw	-41			; 2.6
	dw	-41			; 2.8
	dw	-41			; 3.0
	dw	-41			; 3.2
TOKEN_END


; Token 411h - Integer mach table on Cladot (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cladot due to mach
TOKEN_BEGIN AIR_CL_ADOT
	dw	0			; 0.0
	dw	0			; 0.2
	dw	410			; 0.4
	dw	1024			; 0.6
	dw	2253			; 0.8
	dw	3482			; 1.0
	dw	2253			; 1.2
	dw	1024			; 1.4
	dw	410			; 1.6
	dw	410			; 1.8
	dw	410			; 2.0
	dw	410			; 2.2
	dw	410			; 2.4
	dw	410			; 2.6
	dw	410			; 2.8
	dw	410			; 3.0
	dw	410			; 3.2
TOKEN_END


; Token 412h - Integer mach table on CLq (fixed 17 elements)
; IN: Mach index
; OUT: Delta CLq due to mach
TOKEN_BEGIN AIR_CL_Q
	dw	0			; 0.0
	dw	0			; 0.2
	dw	-410			; 0.4
	dw	-1024			; 0.6
	dw	-2458			; 0.8
	dw	-2458			; 1.0
	dw	-1024			; 1.2
	dw	-410			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 413h - Integer mach table on Clih (fixed 17 elements)
; IN: Mach index
; OUT: Delta Clih due to mach
TOKEN_BEGIN AIR_CL_IH
	dw	0			; 0.0
	dw	0			; 0.2
	dw	20			; 0.4
	dw	82			; 0.6
	dw	328			; 0.8
	dw	328			; 1.0
	dw	328			; 1.2
	dw	328			; 1.4
	dw	328			; 1.6
	dw	328			; 1.8
	dw	328			; 2.0
	dw	328			; 2.2
	dw	328			; 2.4
	dw	328			; 2.6
	dw	328			; 2.8
	dw	328			; 3.0
	dw	328			; 3.2
TOKEN_END


; Token 420h - Integer mach table on Cmde
;IN:  Mach index  (see Guidlines on Mach Integer Tables)
;OUT: Delta Cmde due to mach
TOKEN_BEGIN AIR_CM_DELTAE
	dw	0			; 0.0
	dw	-20			; 0.2
	dw	-82			; 0.4
	dw	-163			; 0.6
	dw	-318			; 0.8
	dw	-207			; 1.0
	dw	-205			; 1.2
	dw	-102			; 1.4
	dw	0			; 1.6
	dw	51			; 1.8
	dw	102			; 2.0
	dw	102			; 2.2
	dw	102			; 2.4
	dw	102			; 2.6
	dw	102			; 2.8
	dw	102			; 3.0
	dw	102			; 3.2
TOKEN_END


; Token 421h - Integer mach table on Cmadot (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cmadot due to mach
TOKEN_BEGIN AIR_CM_ADOT
	dw	0			; 0.0
	dw	51			; 0.2
	dw	205			; 0.4
	dw	563			; 0.6
	dw	1536			; 0.8
	dw	2048			; 1.0
	dw	0			; 1.2
	dw	-6144			; 1.4
	dw	-8192			; 1.6
	dw	-9216			; 1.8
	dw	-10240			; 2.0
	dw	-10240			; 2.2
	dw	-10240			; 2.4
	dw	-10240			; 2.6
	dw	-10240			; 2.8
	dw	-10240			; 3.0
	dw	-10240			; 3.2
TOKEN_END


; Token 422h - Integer mach table on Cmq (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cmq due to mach
TOKEN_BEGIN AIR_CM_Q
	dw	0			; 0.0
	dw	0			; 0.2
	dw	-128			; 0.4
	dw	-256			; 0.6
	dw	-384			; 0.8
	dw	-512			; 1.0
	dw	-384			; 1.2
	dw	-256			; 1.4
	dw	-128			; 1.6
	dw	0			; 1.8
	dw	256			; 2.0
	dw	512			; 2.2
	dw	512			; 2.4
	dw	512			; 2.6
	dw	512			; 2.8
	dw	512			; 3.0
	dw	512			; 3.2
TOKEN_END


; Token 423h - Integer mach table on Cmih (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cmih due to mach
TOKEN_BEGIN AIR_CM_IH
	dw	0			; 0.0
	dw	102			; 0.2
	dw	205			; 0.4
	dw	410			; 0.6
	dw	1024			; 0.8
	dw	717			; 1.0
	dw	717			; 1.2
	dw	717			; 1.4
	dw	717			; 1.6
	dw	717			; 1.8
	dw	717			; 2.0
	dw	717			; 2.2
	dw	717			; 2.4
	dw	717			; 2.6
	dw	717			; 2.8
	dw	717			; 3.0
	dw	717			; 3.2
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN AIR_CD_O		; 430h
DATA_LENGTH_039		DD	34
UNKNOWN_DATA_039	DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 001H, 000H, 00dH, 000H, 070H, 000H, 05fH, 000H
					DB 05fH, 000H, 05fH, 000H, 05fH, 000H, 05fH, 000H
					DB 05fH, 000H, 05fH, 000H, 05fH, 000H, 05fH, 000H
					DB 05fH, 000H
TOKEN_END


; Token 433h - Integer mach table on Cm0 (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cm0 due to mach
TOKEN_BEGIN AIR_CMO
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	1			; 0.8
	dw	5			; 1.0
	dw	10			; 1.2
	dw	6			; 1.4
	dw	6			; 1.6
	dw	6			; 1.8
	dw	6			; 2.0
	dw	6			; 2.2
	dw	6			; 2.4
	dw	6			; 2.6
	dw	6			; 2.8
	dw	6			; 3.0
	dw	6			; 3.2
TOKEN_END


; Token 440h - Integer mach table on Cyb (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cyb due to mach
TOKEN_BEGIN AIR_CY_BETA
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 441h - Integer mach table on Cydr (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cydr due to mach
TOKEN_BEGIN AIR_CY_DELTAR
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	-10			; 0.8
	dw	-10			; 1.0
	dw	-10			; 1.2
	dw	-10			; 1.4
	dw	-10			; 1.6
	dw	-10			; 1.8
	dw	-10			; 2.0
	dw	-10			; 2.2
	dw	-10			; 2.4
	dw	-10			; 2.6
	dw	-10			; 2.8
	dw	-10			; 3.0
	dw	-10			; 3.2
TOKEN_END


; Token 442h - Integer mach table on Cyr (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cyr due to mach
TOKEN_BEGIN AIR_CY_R
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 443h - Integer mach table on Cyp (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cyp due to mach
TOKEN_BEGIN AIR_CY_P
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 450h - Integer mach table on Clb (fixed 17 elements)
; IN: Mach index
; OUT: Delta Clb due to mach
TOKEN_BEGIN AIR_CL_BETA
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 451h - Scalar on ClBeta due to angle of attack  (max 9 entries)
; IN:  Angle of attack (degrees)
; OUT: Scalar on ClBeta
TOKEN_BEGIN AIR_70S_ALPHA_ON_CLDA
	dd	9		; Number of Entries
	REAL8	-180.000000,	1.000000
	REAL8	-90.000000,	0.001000
	REAL8	-14.000000,	-0.050000
	REAL8	-12.000000,	0.650000
	REAL8	0.000000,	1.000000
	REAL8	12.000000,	0.650000
	REAL8	14.000000,	-0.050000
	REAL8	90.000000,	0.001000
	REAL8	180.000000,	1.000000
TOKEN_END


; Token 452h - Integer mach table on Cldr (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cldr due to mach
TOKEN_BEGIN AIR_CL_DELTAR
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 453h - Integer mach table on Clda (fixed 17 elements)
; IN: Mach index
; OUT: Delta Clda due to mach
TOKEN_BEGIN AIR_CL_DELTAA
	dw	0			; 0.0
	dw	0			; 0.2
	dw	-10			; 0.4
	dw	-21			; 0.6
	dw	-41			; 0.8
	dw	-51			; 1.0
	dw	-51			; 1.2
	dw	-51			; 1.4
	dw	-51			; 1.6
	dw	-51			; 1.8
	dw	-51			; 2.0
	dw	-51			; 2.2
	dw	-51			; 2.4
	dw	-51			; 2.6
	dw	-51			; 2.8
	dw	-51			; 3.0
	dw	-51			; 3.2
TOKEN_END


; Token 454h - Integer mach table on Clr (fixed 17 elements)
; IN: Mach index
; OUT: Delta Clr due to mach
TOKEN_BEGIN AIR_CL_R
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 455h - Integer mach table on Clp (fixed 17 elements)
; IN: Mach index
; OUT: Delta Clp due to mach
TOKEN_BEGIN AIR_CL_P
	dw	0			; 0.0
	dw	-10			; 0.2
	dw	-41			; 0.4
	dw	-102			; 0.6
	dw	-205			; 0.8
	dw	-225			; 1.0
	dw	-225			; 1.2
	dw	-225			; 1.4
	dw	-225			; 1.6
	dw	-225			; 1.8
	dw	-225			; 2.0
	dw	-225			; 2.2
	dw	-225			; 2.4
	dw	-225			; 2.6
	dw	-225			; 2.8
	dw	-225			; 3.0
	dw	-225			; 3.2
TOKEN_END


; Token 456h - Scalar on Clp due to angle of attack  (max 9 entries)
; IN:  Angle of attack (degrees)
; OUT: Scalar on Clp
TOKEN_BEGIN AIR_ALPHA_ON_CLP
	dd	9		; Number of Entries
	REAL8	-180.000000,	1.000000
	REAL8	-90.000000,	0.001000
	REAL8	-14.000000,	-0.100000
	REAL8	-12.000000,	0.600000
	REAL8	0.000000,	1.000000
	REAL8	10.000000,	0.600000
	REAL8	12.000000,	-0.100000
	REAL8	90.000000,	0.001000
	REAL8	180.000000,	1.000000
TOKEN_END


; Token 459h - Integer mach table on Cnb (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cnb due to mach
TOKEN_BEGIN AIR_CN_BETA
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 460h - Scalar on CnBeta due to angle of attack  (max 9 entries)
; IN:  Angle of attack (degrees)
; OUT: Scalar on CnBeta
TOKEN_BEGIN AIR_ALPHA_ON_CN_BETA
	dd	9		; Number of Entries
	REAL8	-180.000000,	1.000000
	REAL8	-90.000000,	0.000000
	REAL8	-15.000000,	0.000000
	REAL8	-10.000000,	0.350000
	REAL8	0.000000,	1.000000
	REAL8	10.000000,	0.350000
	REAL8	15.000000,	0.000000
	REAL8	90.000000,	0.000000
	REAL8	180.000000,	1.000000
TOKEN_END


; Token 461h - Integer mach table on Cndr (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cndr due to mach
TOKEN_BEGIN AIR_CN_DELTAR
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 462h - Integer mach table on Cnda (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cnda due to mach
TOKEN_BEGIN AIR_CN_DELTAA
	dw	0			; 0.0
	dw	0			; 0.2
	dw	-2			; 0.4
	dw	-4			; 0.6
	dw	-6			; 0.8
	dw	-6			; 1.0
	dw	-6			; 1.2
	dw	-6			; 1.4
	dw	-6			; 1.6
	dw	-6			; 1.8
	dw	-6			; 2.0
	dw	-6			; 2.2
	dw	-6			; 2.4
	dw	-6			; 2.6
	dw	-6			; 2.8
	dw	-6			; 3.0
	dw	-6			; 3.2
TOKEN_END


; Token 463h - Integer mach table on Cnr (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cnr due to mach
TOKEN_BEGIN AIR_CN_R
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 464h - Scalar on Cnr due to angle of attack  (max 9 entries)
; IN:  Angle of attack (degrees)
; OUT: Scalar on Cnr
TOKEN_BEGIN AIR_ALPHA_ON_CNR
	dd	9		; Number of Entries
	REAL8	-180.000000,	1.000000
	REAL8	-90.000000,	0.001000
	REAL8	-14.000000,	-0.050000
	REAL8	-12.000000,	0.400000
	REAL8	0.000000,	1.000000
	REAL8	12.000000,	0.400000
	REAL8	14.000000,	-0.050000
	REAL8	90.000000,	0.001000
	REAL8	180.000000,	1.000000
TOKEN_END


; Token 465h - Integer mach table on Cnp (fixed 17 elements)
; IN: Mach index
; OUT: Delta Cnp due to mach
TOKEN_BEGIN AIR_CN_P
	dw	0			; 0.0
	dw	0			; 0.2
	dw	0			; 0.4
	dw	0			; 0.6
	dw	0			; 0.8
	dw	0			; 1.0
	dw	0			; 1.2
	dw	0			; 1.4
	dw	0			; 1.6
	dw	0			; 1.8
	dw	0			; 2.0
	dw	0			; 2.2
	dw	0			; 2.4
	dw	0			; 2.6
	dw	0			; 2.8
	dw	0			; 3.0
	dw	0			; 3.2
TOKEN_END


; Token 473h - CM vs. Alpha
;The first entry defines the number of data points (maximum 47 entries)
TOKEN_BEGIN AIR_CM_ALPHA
	dd	19		; Number of Entries
	REAL8	-3.141593,	-2.000000
	REAL8	-0.436330,	-0.626410
	REAL8	-0.169620,	-0.330000
	REAL8	-0.082350,	-0.188000
	REAL8	-0.030000,	-0.100000
	REAL8	0.051000,	0.000000
	REAL8	0.127070,	0.090880
	REAL8	0.161980,	0.138660
	REAL8	0.179430,	0.161280
	REAL8	0.196880,	0.179360
	REAL8	0.214340,	0.197420
	REAL8	0.231790,	0.190440
	REAL8	0.249240,	0.180740
	REAL8	0.266700,	0.169660
	REAL8	0.301060,	0.135040
	REAL8	0.345240,	0.247530
	REAL8	0.388870,	0.100410
	REAL8	0.593402,	0.006233
	REAL8	3.141593,	2.000000
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_61S_HYDRAULICS		; 513h
DATA_LENGTH_040		DD	36
UNKNOWN_DATA_040	DB 002H, 000H, 000H, 000H, 09aH, 099H, 099H, 099H
					DB 099H, 099H, 0e9H, 03fH, 000H, 000H, 000H, 000H
					DB 000H, 05eH, 01aH, 041H, 07bH, 014H, 0aeH, 047H
					DB 0e1H, 07aH, 084H, 03fH, 001H, 000H, 000H, 000H
					DB 002H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_61S_HYDRAULIC_PRESSURE_TABLE		; 514h
DATA_LENGTH_041		DD	84
UNKNOWN_DATA_041	DB 005H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 040H, 0afH, 040H, 000H, 000H, 000H, 000H
					DB 080H, 0a2H, 019H, 041H, 000H, 000H, 000H, 000H
					DB 000H, 094H, 0bbH, 040H, 000H, 000H, 000H, 000H
					DB 080H, 0a2H, 019H, 041H, 000H, 000H, 000H, 000H
					DB 000H, 07cH, 0d5H, 040H, 000H, 000H, 000H, 000H
					DB 080H, 0a2H, 019H, 041H, 000H, 000H, 000H, 000H
					DB 000H, 038H, 0ddH, 040H, 000H, 000H, 000H, 000H
					DB 0c0H, 0c1H, 019H, 041H
TOKEN_END


;  Token 516h - Scalar affect of aileron and rudder trim
;0 implies no trim
TOKEN_BEGIN AIR_61S_AIL_RUD_TRIM_CONSTANTS
	REAL8	-0.200000		; cl_delta_ailertrim
	REAL8	0.200000		; cn_delta_rudtrim
TOKEN_END


; Token 517h - Elevator elasticity on effectiveness scaling table  (max 5 entries)
; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2) (psf)
; OUT: Effectiveness scalar
TOKEN_BEGIN AIR_61S_ELEVATOR_ELASTICITY
	dd	5		; Number of Entries
	REAL8	0.000000,	1.000000
	REAL8	135.000000,	1.000000
	REAL8	300.000000,	1.000000
	REAL8	1000.000000,	1.000000
	REAL8	1500.000000,	1.000000
TOKEN_END


; Token 518h - Aileron elasticity on effectiveness scaling table  (max 5 entries)
; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2) (psf)
; OUT: Effectiveness scalar
; q=.5rhoV^2
TOKEN_BEGIN AIR_61S_AILERON_ELASTICITY
	dd	5		; Number of Entries
	REAL8	0.000000,	1.000000
	REAL8	300.000000,	0.700000
	REAL8	600.000000,	0.700000
	REAL8	1482.000000,	0.700000
	REAL8	1500.000000,	0.700000
TOKEN_END


; Token 519h - Rudder elasticity on effectiveness scaling table  (max 5 entries)
; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2) (psf)
; OUT: Effectiveness scalar
; q=.5rhoV^2
TOKEN_BEGIN AIR_61S_RUDDER_ELASTICITY
	dd	5		; Number of Entries
	REAL8	0.000000,	1.000000
	REAL8	300.000000,	1.000000
	REAL8	800.000000,	1.000000
	REAL8	1000.000000,	1.000000
	REAL8	1500.000000,	1.000000
TOKEN_END


; Token 540h - Exhaust Gas Temperature
TOKEN_BEGIN AIR_61S_EGT
	REAL8	1.000000		; EGT tuning constant
	REAL8	1400.000000		; EGT peak temperature (typical peak: 1200 degF + 460)
	REAL8	0.200000		; EGT time constant
TOKEN_END


; Token 543h - Oil Temperature
TOKEN_BEGIN AIR_61S_OIL_TEMPERATURE
	REAL8	1.000000		; Oil temp tuning constant
	REAL8	0.000000		; Oil temp cooling constant
	REAL8	680.000000		; Max Oil Temp (deg Rankine)
	REAL8	0.020000		; Oil temp time constant
TOKEN_END


; Token 544h - Oil Pressure
TOKEN_BEGIN AIR_61S_OIL_PRESSURE
	REAL8	1.000000		; Oil pressure tuning constant
	REAL8	40000.000000		; Oil pressure max (PSF)
	REAL8	0.800000		; Oil pressure time constant
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_ENGINE_POSITIONS		; 1002h
DATA_LENGTH_042		DD	48
UNKNOWN_DATA_042	DB 09aH, 0ffH, 0ffH, 0ffH, 0d7H, 0ffH, 0ffH, 0ffH
					DB 012H, 0feH, 0ffH, 0ffH, 000H, 000H, 000H, 000H
					DB 0daH, 0ffH, 0ffH, 0ffH, 090H, 0fdH, 0ffH, 0ffH
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN AIR_VARIABLES		; 1101h
DATA_LENGTH_043		DD	250
UNKNOWN_DATA_043	DB 047H, 000H, 09cH, 000H, 080H, 0a2H, 000H, 000H
					DB 000H, 000H, 000H, 080H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 02eH, 040H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 040H, 0a9H, 006H, 001H, 000H
					DB 03eH, 009H, 000H, 000H, 000H, 000H, 0a6H, 027H
					DB 0a0H, 00eH, 008H, 0f5H, 0f8H, 00aH, 0b0H, 0f8H
					DB 046H, 000H, 0c8H, 000H, 03bH, 000H, 04dH, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 04aH, 0ffH, 061H, 02cH, 000H, 000H, 000H, 0a0H
					DB 0ffH, 0ffH, 034H, 0ffH, 033H, 007H, 09aH, 099H
					DB 099H, 099H, 099H, 099H, 0e9H, 03fH, 09aH, 099H
					DB 099H, 099H, 099H, 099H, 0c9H, 0bfH, 059H, 000H
					DB 029H, 0feH, 020H, 000H, 000H, 000H, 056H, 0f0H
					DB 0ffH, 0ffH, 070H, 0feH, 0ffH, 0ffH, 0d7H, 0a3H
					DB 070H, 03dH, 00aH, 0d7H, 0c3H, 03fH, 028H, 000H
					DB 000H, 000H, 0a6H, 0caH, 000H, 000H, 09aH, 0f1H
					DB 0ffH, 0ffH, 09aH, 00cH, 000H, 000H, 0d0H, 037H
					DB 0f8H, 0ffH, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 0c0H, 09aH, 099H, 099H, 099H, 099H, 099H
					DB 0c9H, 03fH, 07bH, 014H, 0aeH, 047H, 0e1H, 07aH
					DB 094H, 03fH, 093H, 018H, 004H, 056H, 00eH, 02dH
					DB 0b2H, 0bfH, 064H, 001H, 000H, 000H, 0f1H, 0ffH
					DB 0c4H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 06eH, 000H, 000H, 000H
					DB 080H, 0f3H, 000H, 000H, 000H, 000H, 0efH, 0fdH
					DB 096H, 0ffH, 050H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H
TOKEN_END


; Token 1199h - PID CONTROLLERS
TOKEN_BEGIN AIR_AP_PID_CONTROLLERSF
	REAL8	380.000000,	0.000000,	0.000000,	8.000000,	30.000000,	0.000000,	30.000000
	REAL8	1.500000,	0.000000,	0.000000,	4.000000,	2.000000,	0.000000,	20.000000
	REAL8	0.000029,	0.000000,	0.000000,	0.000250,	1000.000000,	0.000000,	1000.000000
	REAL8	61.000000,	0.000000,	0.000000,	85.520300,	10.000000,	0.000000,	10.000000
	REAL8	12.000000,	0.050000,	0.000000,	4.000000,	5.000000,	0.000000,	2.000000
	REAL8	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000
	REAL8	6.500000,	0.000000,	0.000000,	0.000800,	0.700000,	3.500000,	0.700000
	REAL8	670.000000,	0.000000,	0.000000,	1.000000,	200.000000,	0.000000,	200.000000
	REAL8	35.000000,	0.000000,	0.000000,	0.000000,	140.000000,	0.000000,	140.000000
	REAL8	2000.000000,	0.000000,	0.000000,	0.100000,	50.000000,	0.000000,	50.000000
	REAL8	4000.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	50.000000
	REAL8	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000
	REAL8	0.400000,	0.001000,	0.000000,	15.000000,	10.000000,	0.000000,	40.000000
	REAL8	0.000029,	0.000000,	0.000000,	0.000200,	1000.000000,	0.000000,	1000.000000
	REAL8	2.500000,	0.000000,	0.000000,	10.000000,	0.000000,	0.000000,	100.000000
	REAL8	1.000000,	0.025000,	0.090000,	30.000000,	1.000000,	0.000000,	25.000000
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_AP_ELEVTRM_IN_BANK		; 1202h
DATA_LENGTH_044		DD	4
UNKNOWN_DATA_044	DB 03eH, 009H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_AP_LIMITS		; 1203h
DATA_LENGTH_045		DD	36
UNKNOWN_DATA_045	DB 000H, 000H, 000H, 000H, 000H, 000H, 039H, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 034H, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 069H, 040H
					DB 000H, 000H, 000H, 000H, 000H, 080H, 061H, 040H
					DB 01cH, 007H, 0acH, 0eaH
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_70_TURBINE_ENGINE		; 1501h
DATA_LENGTH_046		DD	52
UNKNOWN_DATA_046	DB 000H, 000H, 000H, 000H, 000H, 0d7H, 0cdH, 040H
					DB 014H, 0aeH, 047H, 0e1H, 07aH, 094H, 02cH, 040H
					DB 0fcH, 0a9H, 0f1H, 0d2H, 04dH, 062H, 070H, 03fH
					DB 000H, 000H, 000H, 000H, 000H, 0daH, 0c6H, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 0f0H, 03fH, 000H, 000H, 000H, 000H
					DB 000H, 000H, 0f0H, 03fH
TOKEN_END


; Token 1502h - N1 vs N2 & Mach lookup table (max 13 rows, 11 columns)
;IN: X:  Mach
;IN: Y:  N2 (corrected)
;OUT: N1 (corrected)
TOKEN_BEGIN AIR_70_N2_TO_N1_TABLE
	UINT32	13,	3
	REAL8	0.000000,	0.000000,	0.850000
	REAL8	0.000000,	0.000000,	22.000000
	REAL8	10.000000,	0.100000,	24.000000
	REAL8	20.000000,	2.700000,	37.400000
	REAL8	30.000000,	12.700000,	48.000000
	REAL8	61.000000,	54.000000,	65.000000
	REAL8	74.000000,	63.500000,	69.000000
	REAL8	78.500000,	68.000000,	71.100000
	REAL8	84.000000,	75.000000,	76.000000
	REAL8	86.500000,	77.000000,	78.800000
	REAL8	89.500000,	82.000000,	83.100000
	REAL8	92.500000,	87.000000,	87.500000
	REAL8	100.000000,	93.000000,	92.000000
TOKEN_END


; Token 1503h - Commanded N2 (corrected) vs. Throttle table at 0 Mach (max 9 rows, 11 columns)
; NOTE:  The specific (low) Mach value is specified at the 0,0 position of the table
; This table is used in conjunction with the AIR_70_MACH_HI_CORRECTED_COMMANDED_NE table
; IN: X: 1/atmospheric press ratio (Psl/P)(note: use inverse of delta pressure ratio so that values are in increasing order)
; IN: Y: %Power Lever / Throttle
; OUT: Corrected N2 for MACH = 0
TOKEN_BEGIN AIR_70_MACH_0_CORRECTED_COMMANDED_NE
	UINT32	9,	3
	REAL8	0.000000,	1.000000,	4.484000
	REAL8	0.000000,	61.000000,	75.000000
	REAL8	0.400000,	70.500000,	78.000000
	REAL8	0.500000,	78.500000,	80.500000
	REAL8	0.600000,	83.000000,	83.500000
	REAL8	0.700000,	86.500000,	86.800000
	REAL8	0.800000,	89.500000,	89.800000
	REAL8	0.880000,	93.000000,	92.700000
	REAL8	1.000000,	100.000000,	98.000000
TOKEN_END


; Token 1504h - Commanded N2 (corrected) vs. Throttle table at HI Mach (max 9 rows, 11 columns)
; NOTE:  The specific (HI) Mach value is specified at the 0,0 position of the table
; This table is used in conjunction with the AIR_70_MACH_0_CORRECTED_COMMANDED_NE table
; IN: X: 1/atmospheric press ratio (Psl/P)(note: use inverse of delta pressure ratio so that values are in increasing order)
; IN: Y: %Power Lever / Throttle
; OUT: Corrected N2 for specified MACH
TOKEN_BEGIN AIR_70_MACH_HI_CORRECTED_COMMANDED_NE
	UINT32	9,	3
	REAL8	0.900000,	1.000000,	4.484000
	REAL8	0.000000,	65.000000,	77.000000
	REAL8	0.400000,	73.000000,	79.000000
	REAL8	0.500000,	78.500000,	81.000000
	REAL8	0.600000,	83.000000,	84.500000
	REAL8	0.700000,	87.000000,	87.200000
	REAL8	0.800000,	91.000000,	89.800000
	REAL8	0.900000,	94.500000,	92.700000
	REAL8	1.000000,	100.000000,	98.000000
TOKEN_END


; Token 1505h - ;N2 (Corrected) vs. FuelFlow constant
; where the constant is a normalized ratio of actual fuelflow parameter to static thrust
; IN:  Normalized Fuelflow constant
; OUT: N2 (corrected)
TOKEN_BEGIN AIR_70_CORRECTED_N2_FROM_FF
	UINT32	10
	REAL8	0.450000,	22.500000
	REAL8	1.000000,	35.000000
	REAL8	1.200000,	45.000000
	REAL8	1.300000,	55.000000
	REAL8	1.320000,	60.000000
	REAL8	1.370000,	75.000000
	REAL8	1.440000,	90.000000
	REAL8	1.485000,	100.000000
	REAL8	1.650000,	108.000000
	REAL8	1.660000,	115.000000
TOKEN_END


; Token 1506h - N1 vs Thrust table (max 21 rows, 11 columns)
;IN: X: Mach
;IN: Y: N1 (corrected)
;OUT: Gross Thurst (corrected) / static thrust)
TOKEN_BEGIN AIR_70_N1_AND_MACH_ON_THRUST
	UINT32	21,	8
	REAL8	0.000000,	0.000000,	0.150000,	0.350000,	0.500000,	0.600000,	0.700000,	0.850000
	REAL8	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000,	0.000000
	REAL8	20.000000,	0.015000,	0.016000,	0.020000,	0.030000,	0.045000,	0.070000,	0.120000
	REAL8	25.000000,	0.030000,	0.025500,	0.030000,	0.040000,	0.057000,	0.085000,	0.150000
	REAL8	30.000000,	0.040000,	0.040000,	0.040000,	0.070000,	0.085000,	0.130000,	0.200000
	REAL8	35.000000,	0.050000,	0.060000,	0.060000,	0.084000,	0.106000,	0.170000,	0.240000
	REAL8	40.000000,	0.070000,	0.080000,	0.080000,	0.100000,	0.125000,	0.220000,	0.300000
	REAL8	45.000000,	0.100000,	0.100000,	0.115000,	0.140000,	0.170000,	0.270000,	0.360000
	REAL8	50.000000,	0.130000,	0.120000,	0.140000,	0.180000,	0.230000,	0.330000,	0.430000
	REAL8	55.000000,	0.160000,	0.150000,	0.180000,	0.230000,	0.300000,	0.400000,	0.520000
	REAL8	60.000000,	0.190000,	0.200000,	0.230000,	0.290000,	0.380000,	0.480000,	0.610000
	REAL8	65.000000,	0.230000,	0.240000,	0.280000,	0.375000,	0.480000,	0.580000,	0.720000
	REAL8	70.000000,	0.300000,	0.300000,	0.350000,	0.470000,	0.580000,	0.700000,	0.850000
	REAL8	75.000000,	0.400000,	0.380000,	0.430000,	0.580000,	0.710000,	0.830000,	1.000000
	REAL8	80.000000,	0.500000,	0.500000,	0.550000,	0.720000,	0.870000,	1.000000,	1.180000
	REAL8	85.000000,	0.670000,	0.670000,	0.710000,	0.900000,	1.080000,	1.230000,	1.430000
	REAL8	90.000000,	0.860000,	0.860000,	0.900000,	1.130000,	1.330000,	1.500000,	1.700000
	REAL8	95.000000,	1.100000,	1.100000,	1.150000,	1.450000,	1.640000,	1.800000,	2.050000
	REAL8	100.000000,	1.650000,	1.670000,	1.700000,	1.800000,	1.950000,	2.140000,	2.400000
	REAL8	105.000000,	1.650000,	1.670000,	1.700000,	1.800000,	1.950000,	2.150000,	2.400000
	REAL8	115.000000,	1.650000,	1.670000,	1.700000,	1.800000,	1.950000,	2.150000,	2.400000
TOKEN_END


; Token 1507h - N1 vs AirFlow/Ram Drag   (max 21 rows, 11 columns)
;IN: X:  Mach
;IN: Y:  N1 (corrected)
;OUT: Normalized Airflow (Corrected) = Airflow / inlet area
TOKEN_BEGIN AIR_70_CORRECTED_AIRFLOW
	UINT32	9,	3
	REAL8	0.000000,	0.000000,	0.800000
	REAL8	0.000000,	0.000000,	0.000000
	REAL8	20.000000,	0.000000,	14.000000
	REAL8	40.000000,	0.000000,	24.000000
	REAL8	60.000000,	0.000000,	25.000000
	REAL8	70.000000,	0.000000,	27.000000
	REAL8	80.000000,	0.000000,	28.000000
	REAL8	90.000000,	0.000000,	29.000000
	REAL8	100.000000,	0.000000,	30.000000
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_70_VACUUM_SYSTEM		; 1512h
DATA_LENGTH_047		DD	60
UNKNOWN_DATA_047	DB 001H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 09aH, 099H, 099H, 099H, 099H, 099H, 014H, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 0c0H, 03fH
					DB 033H, 033H, 033H, 033H, 033H, 033H, 0ebH, 03fH
					DB 033H, 033H, 033H, 033H, 033H, 033H, 010H, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 00cH, 040H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_70_WING_SPECS_2		; 1515h
DATA_LENGTH_048		DD	40
UNKNOWN_DATA_048	DB 0cdH, 0ccH, 0ccH, 0ccH, 0ccH, 04cH, 031H, 040H
					DB 0cdH, 0ccH, 0ccH, 0ccH, 0ccH, 04cH, 011H, 040H
					DB 05aH, 064H, 03bH, 0dfH, 04fH, 08dH, 0e3H, 03fH
					DB 066H, 066H, 066H, 066H, 066H, 066H, 038H, 040H
					DB 08fH, 0c2H, 0f5H, 028H, 05cH, 08fH, 0d2H, 03fH
TOKEN_END


; Token 1524h - Dynamic primary exhaust nozzle available flag
TOKEN_BEGIN AIR_70_PRIMARY_NOZZLE
	BOOL	FALSE		; fVariablePrimaryNozzle
TOKEN_END


; Token 1522h - Thrust reverser flags
TOKEN_BEGIN AIR_70_REVERSER_NOZZLE
	BOOL	TRUE		; fReverserNozzle
	BOOL	FALSE		; fMachControlledReverserNozzle
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN AIR_70_VARIABLE_INLET		; 1523h
DATA_LENGTH_049		DD	4
UNKNOWN_DATA_049	DB 000H, 000H, 000H, 000H
TOKEN_END


; Token 1524h - Afterburner on thrust table (max 10 entries)
;IN:  Mach
;OUT: Scalar on Thrust for max afterburner.
;     Output is scaled by percent afterburner active)
TOKEN_BEGIN AIR_70_AFTERBURNER_ON_THRUST_TABLE
	UINT32	10
	REAL8	0.000000,	1.000000
	REAL8	0.200000,	1.000000
	REAL8	0.400000,	1.000000
	REAL8	0.600000,	1.000000
	REAL8	0.800000,	1.000000
	REAL8	1.000000,	1.000000
	REAL8	1.200000,	1.000000,	1.400000,	1.000000,	1.600000,	1.000000,	1.800000,	1.000000
TOKEN_END


; Token 1525h - Elevator trim elasticity on effectiveness scaling table  (max 5 entries)
; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2) (psf)
; OUT: Effectiveness scalar
; q=.5rhoV^2
TOKEN_BEGIN AIR_70_ELEVATOR_TRIM_ELASTICITY
	dd	5		; Number of Entries
	REAL8	0.000000,	1.000000
	REAL8	100.000000,	1.000000
	REAL8	800.000000,	1.000000
	REAL8	1000.000000,	1.000000
	REAL8	1500.000000,	1.000000
TOKEN_END


; Token 1526h - Interstage turbine temperature
TOKEN_BEGIN AIR_70_ITT
	REAL8	1.000000		; ITT tuning constant
	REAL8	2000.000000		; ITT peak temperature
	REAL8	2.000000		; ITT time constant
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN UNUSED_AIR_70_FLAPS_NONLINEAR_TABLE		; 1531h
DATA_LENGTH_050		DD	52
UNKNOWN_DATA_050	DB 003H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 046H, 05dH, 06bH, 0efH
					DB 053H, 055H, 0d5H, 03fH, 046H, 05dH, 06bH, 0efH
					DB 053H, 055H, 0d5H, 03fH, 000H, 000H, 000H, 000H
					DB 000H, 000H, 0f0H, 03fH, 000H, 000H, 000H, 000H
					DB 000H, 000H, 0f0H, 03fH
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN OBSOLETE_AIR_70_FLIGHT_DIRECTOR		; 1533h
DATA_LENGTH_051		DD	4
UNKNOWN_DATA_051	DB 000H, 000H, 000H, 000H
TOKEN_END


; Unknown data section ----------------------------------------------
TOKEN_BEGIN AIR_70_AERODYNAMIC_CENTER		; 1534h
DATA_LENGTH_052		DD	24
UNKNOWN_DATA_052	DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H
					DB 066H, 066H, 066H, 066H, 066H, 066H, 014H, 0c0H
TOKEN_END

sim_size        equ     $ - sim_data

	end
