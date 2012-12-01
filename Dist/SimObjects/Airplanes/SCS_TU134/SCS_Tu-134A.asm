; Copyright (c) Lockheed Martin Corporation.  All rights reserved.
; Sample Jet flight dynamics file
;
;
 
        include asm.inc         ; include this in ALL .asm files!
        include airtoken.inc    ; definitions of token macros
        include sim1.inc        ; definitions of token values

.data

sim_data        label   byte
        
      	;******START OF AERODYNAMIC DATA ************************************************************************************
	;********************************************************************************************************************


	
	;**** BEGINNING OF REQUIRED AERODYNAMICS ************************

	;The following 6 blocks define the base stability and control derivatives
	;Lift, Drag, Pitch, Side Force, Roll, and Yaw.

        TOKEN_BEGIN	AIR_80_LIFT_PARAMS
		REAL8	-0.480000	; CL spoiler
		REAL8	0.491244	; CL flaps
		REAL8	0.000000	; UNUSED
		REAL8	0.353935	; CLih
		REAL8	-0.134961	; CLde
		REAL8	0.000000	; UNUSED
	TOKEN_END

	TOKEN_BEGIN	AIR_80_DRAG_PARAMS
		REAL8	0.051         	; CDo
		REAL8	0.080000	; CD flaps
		REAL8	0.007000	; CD gear
		REAL8	0.130000	; CD spoiler
	TOKEN_END

	TOKEN_BEGIN	AIR_80_PITCH_PARAMS
		REAL8	-1.423802	; CMih
		REAL8	-1.4     	; CMde
		REAL8	0.000000	; CMde due to propwash
		REAL8	-3.966478	; CLq
		REAL8	0.770403	; CL adot
		REAL8	5.099159	; CM adot
		REAL8	-91.0	        ; CMq
		REAL8	0.000000	; CMq due to propwash
		REAL8	-0.02     	; CMo
		REAL8	-0.002		; CM flap
		REAL8	-7.119009	; CM delta trim
		REAL8	0.00000 	; CM gear
		REAL8	0.010000	; CM spoiler
	TOKEN_END

	TOKEN_BEGIN	AIR_80_SIDE_FORCE_PARAMS
		REAL8	-0.678522	; CyB
		REAL8	0.029355	; CyP
		REAL8	0.061966	; CyR
		REAL8	-0.193005	; Cy Delta Rudder
	TOKEN_END

	TOKEN_BEGIN	AIR_80_ROLL_PARAMS
		REAL8	0.157221	; ClB
		REAL8	-4.134894	; ClP
		REAL8	-0.162191	; ClR
		REAL8	0.123552	; Cl Delta Spoiler
		REAL8	-0.197583	; Cl Delta Aileron
		REAL8	0.024785	; Cl Delta Rudder
	TOKEN_END

	TOKEN_BEGIN	AIR_80_YAW_PARAMS
		REAL8	0.322632	; CnB
		REAL8	0.210647	; CnP
		REAL8	-2.520723	; CnR
		REAL8	0.000000	; CnR due to propwash
		REAL8	0.000000	; UNUSED
		REAL8	0.000000	; UNUSED
		REAL8	-0.002180	; Cn Delta Aileron
		REAL8	0.116691	; Cn Delta Rudder
		REAL8	0.000000	; Cn Delta Rudder due to propwash
	TOKEN_END

	;CL vs. Alpha
	;The first entry defines the number of data points (maximum 47 entries)
	;DONE 
        TOKEN_BEGIN     AIR_CL_ALPHA
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

	;CM vs. Alpha
	;The first entry defines the number of data points (maximum 47 entries)
        TOKEN_BEGIN     AIR_CM_ALPHA
               dd	13 	; Number of Entries
               REAL8    -3.142,   0.000 
               REAL8    -0.541,  -0.528
               REAL8    -0.367,  -0.528
               REAL8    -0.297,  -0.264
               REAL8    -0.279,  -0.220
               REAL8    -0.262,  -0.183
               REAL8     0.000,   0.000 
               REAL8     0.262,   0.183 
               REAL8     0.279,   0.220 
               REAL8     0.297,   0.264 
               REAL8     0.367,   0.528 
               REAL8     0.541,   0.528 
               REAL8     3.142,   0.000 
	TOKEN_END                

	;**** END OF REQUIRED AERODYNAMICS ************************************************

	;**** GROUND EFFECT ************************
	;Scalar on Lift due to ground proximity  (max 11 entries)
	;IN:  Ratio of wingspan / height above ground
	;OUT: Scalar on CL
	;DONE
	TOKEN_BEGIN     AIR_GROUND_EFFECT
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

	;**** END OF GROUND EFFECT ************************

	;**** BEGINNING OF ADDITIONAL CONTROL EFFECTS *************

	;Scalar affect of aileron and rudder trim
	;0 implies no trim
        TOKEN_BEGIN     AIR_61S_AIL_RUD_TRIM_CONSTANTS
      	      REAL8  -0.2 ;cl_delta_ailertrim
	      REAL8   0.2 ;cn_delta_rudtrim
        TOKEN_END

	;Elevator effectiveness scaling table (max 7 entries)
	; IN:  Elevator angle  (radians)
	; OUT: Effectiveness scalar
        TOKEN_BEGIN     AIR_ELEVATOR_SCALING       
        UINT32  7               ;NUMBER OF ENTRIES

        REAL8   -0.349, 1.0     ;-20 DEG
        REAL8   -0.262, 1.0     ;-15 DEG
        REAL8   -0.175, 1.0     ;-10 DEG
        REAL8   0.0,    1.0
        REAL8   0.175,  1.0     ;10 DEG
        REAL8   0.262,  1.0     ;15 DEG
        REAL8   0.296,  1.0     ;17 DEG

        TOKEN_END

        ;Aileron effectiveness scaling table  (max 7 entries)
	; IN:  Aileron angle  (radians)
	; OUT: Effectiveness scalar
        TOKEN_BEGIN     AIR_AILERON_SCALING        
        UINT32  7               ;NUMBER OF ENTRIES

        REAL8   -0.785, 1.0     ;-45 DEG
        REAL8   -0.524, 1.0     ;-30 DEG
        REAL8   -0.175, 1.0     ;-10 DEG
        REAL8   0.0,    1.0
        REAL8   0.175,  1.0     ;10 DEG
        REAL8   0.524,  1.0     ;30 DEG
        REAL8   0.785,  1.0     ;45 DEG

        TOKEN_END

	;Rudder effectiveness scaling table  (max 7 entries)
	; IN:  Rudder angle  (radians)
	; OUT: Effectiveness scalar
        TOKEN_BEGIN     AIR_RUDDER_SCALING         
        UINT32  7               ;NUMBER OF ENTRIES

        REAL8   -0.785, 1.0     ;-45 DEG
        REAL8   -0.524, 1.0     ;-30 DEG
        REAL8   -0.175, 1.0     ;-10 DEG
        REAL8   0.0,    1.0
        REAL8   0.175,  1.0     ;10 DEG
        REAL8   0.524,  1.0     ;30 DEG
        REAL8   0.785,  1.0     ;45 DEG

        TOKEN_END

	;Elevator elasticity on effectiveness scaling table  (max 5 entries)
	; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2) (psf)
	; OUT: Effectiveness scalar
        TOKEN_BEGIN     AIR_61S_ELEVATOR_ELASTICITY
        UINT32  5               ;NUMBER OF ENTRIES

                ;q=.5rhoV^2
        REAL8    0.0,           1.0     ;Ve = 0    keas
        REAL8    135.0,         1.0     ;Ve = 200  keas
        REAL8    300.0,         1.0     ;Ve = 297  keas
        REAL8    1000.0,        0.8     ;Ve = 543  keas
        REAL8    1500.0,        0.4     ;Ve = 665  keas

        TOKEN_END

	;Elevator trim elasticity on effectiveness scaling table  (max 5 entries)
	; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2)  (psf)
	; OUT: Effectiveness scalar
        TOKEN_BEGIN     AIR_70_ELEVATOR_TRIM_ELASTICITY      
        UINT32  5               ;NUMBER OF ENTRIES

                ;q=.5rhoV^2
        REAL8    0.0,           1.0     ;Ve = 0    keas
        REAL8    300.0,         0.4     ;Ve = 297  keas
        REAL8    800.0,         0.2     ;Ve = 485  keas
        REAL8    1000.0,        0.2     ;Ve = 543  keas
        REAL8    1500.0,        0.1     ;Ve = 665  keas

        TOKEN_END

	;Aileron elasticity on effectiveness scaling table  (max 5 entries)
	; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2)  (psf)
	; OUT: Effectiveness scalar
        TOKEN_BEGIN     AIR_61S_AILERON_ELASTICITY 
        UINT32  5               ;NUMBER OF ENTRIES

                ;q=.5rhoV^2
        REAL8    0.0,           1.0     ;Ve = 0    keas
        REAL8    300.0,         0.5     ;Ve = 297  keas
        REAL8    600.0,         0.2     ;Ve = 420  keas
        REAL8    1482.0,        0.1     ;Ve = 760 keas
        REAL8    1500.0,        0.1     ;Ve = 665  keas

        TOKEN_END

        ;Rudder elasticity on effectiveness scaling table  (max 5 entries)
	; IN:  Aircraft dynamic pressure ( 1/2 Rho * V^2)  (psf)
	; OUT: Effectiveness scalar
	TOKEN_BEGIN     AIR_61S_RUDDER_ELASTICITY            
        UINT32  5               ;NUMBER OF ENTRIES

                ;q=.5rhoV^2
        REAL8    0.0,           1.0     ;Ve = 0    keas
        REAL8    300.0,         1.0     ;Ve = 297  keas
        REAL8    800.0,         0.5     ;Ve = 485  keas
        REAL8    1000.0,        0.3     ;Ve = 543  keas
        REAL8    1500.0,        0.2     ;Ve = 665  keas

        TOKEN_END

	;Load factor on effectiveness scaling table  (max 5 entries)
	; IN:  Aircraft load factor 
	; OUT: Effectiveness scalar
        TOKEN_BEGIN     AIR_61S_AILERON_LOAD_FACTOR_EFF
                dd      5       ; Number of Entries
                REAL8           0.000000,       1.0        ;
                REAL8           3.000000,       1.0        ;
                REAL8           4.000000,       1.0        ;
                REAL8           6.000000,       1.0        ;
                REAL8           8.000000,       1.0        ;       
        TOKEN_END

       	;**** END OF ADDITIONAL CONTROL EFFECTS *************


	;**** START OF ANGLE OF ATTACK TABLES ***************

	;Cl (roll) induced by angle of attack  (max 7 entries)
	; IN: Angle of attack (degrees)
	; OUT: Delta Cl
        TOKEN_BEGIN     AIR_70S_Cl_ALPHA_ROLL
        UINT32  7               ;NUMBER OF ENTRIES

        REAL8    -17.0,  0.00
        REAL8    -10.0,  0.00
        REAL8     -6.0,  0.00
        REAL8     10.0,  0.00
        REAL8     12.0,  0.00
        REAL8     13.0,  0.00
        REAL8     17.0,  0.00

        TOKEN_END

	;Cn (yaw) induced by angle of attack  (max 7 entries)
	; IN: Angle of attack (degrees)
	; OUT: Delta Cn
        TOKEN_BEGIN     AIR_70S_CN_ALPHA_YAW
        UINT32  7               ;NUMBER OF ENTRIES

        REAL8    -16.0,  0.00
        REAL8    -13.0,  0.00
        REAL8    -10.0,  0.00
        REAL8     10.0,  0.00
        REAL8     11.0,  0.00
        REAL8     13.0,  0.00
        REAL8     15.0,  0.00

        TOKEN_END


      	;Scalar on Cmde due to angle of attack  (max 5 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Cmde
        TOKEN_BEGIN     AIR_61S_ALPHA_ON_CMDE
                dd      5       ; Number of Entries
                REAL8           -15.000000,     1.00000        ;
                REAL8           0.000000,       1.00000        ;
                REAL8           8.000000,       1.00000        ;
                REAL8           15.000000,      1.00000        ;
                REAL8           20.000000,      1.00000        ;       
        TOKEN_END

	;Scalar on Cmih due to angle of attack  (max 5 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Cmih
        TOKEN_BEGIN     AIR_61S_ALPHA_ON_CMIH
                dd      5       ; Number of Entries
                REAL8           -15.000000,     1.000000        ;
                REAL8           0.000000,       1.000000        ;
                REAL8           13.000000,      1.000000        ;
                REAL8           15.000000,      1.000000        ;
                REAL8           25.000000,      1.000000        ;       
        TOKEN_END

	;Scalar on Cmadot due to angle of attack  (max 5 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Cmadot
        TOKEN_BEGIN     AIR_61S_ALPHA_ON_CMADOT
                dd      5       ; Number of Entries
                REAL8           -15.000000,     1.000000        ;
                REAL8           0.000000,       1.000000        ;
                REAL8           5.000000,       1.000000        ;
                REAL8           15.000000,      1.000000        ;
                REAL8           25.000000,      1.000000        ;       
        TOKEN_END

	;Scalar on Cmq due to angle of attack  (max 5 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Cmq
        TOKEN_BEGIN     AIR_61S_ALPHA_ON_CMQ
                dd      5       ; Number of Entries
                REAL8           -15.000000,     1.000000        ;
                REAL8           0.000000,       1.000000        ;
                REAL8           11.000000,      1.000000        ;
                REAL8           15.000000,      1.000000        ;
                REAL8           25.000000,      1.000000        ;       
        TOKEN_END

	;Scalar on Cndr due to angle of attack  (max 5 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Cndr
        TOKEN_BEGIN     AIR_70S_ALPHA_ON_CNDR
                dd      5       ; Number of Entries
                REAL8           -15.000000,     1.000000        ;
                REAL8           0.000000,       1.000000        ;
                REAL8           11.000000,      1.000000        ;
                REAL8           15.000000,      1.000000        ;
                REAL8           25.000000,      1.000000        ;       
        TOKEN_END

	;Scalar on Clda due to angle of attack  (max 5 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Clda
        TOKEN_BEGIN     AIR_70S_ALPHA_ON_CLDA
                dd      5       ; Number of Entries
                REAL8           -15.000000,     1.000000        ;
                REAL8           0.000000,       1.000000        ;
                REAL8           11.000000,      1.000000        ;
                REAL8           15.000000,      1.000000        ;
                REAL8           25.000000,      1.000000        ;       
        TOKEN_END

	;Scalar on ClBeta due to angle of attack  (max 9 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on ClBeta
	TOKEN_BEGIN     AIR_ALPHA_ON_CL_BETA
                dd      9       ; Number of Entries
                REAL8           -180.000000,    1.000000        ;
                REAL8           -90.000000,     1.000000        ;
                REAL8           -15.000000,     1.000000        ;
                REAL8           -10.000000,     1.000000        ;
                REAL8           0.000000,       1.000000        ;
                REAL8           10.000000,      1.000000        ;
                REAL8           15.000000,      1.000000        ;
                REAL8           90.000000,      1.000000        ;
                REAL8           180.000000,     1.000000        ;       
        TOKEN_END        

	;Scalar on Clp due to angle of attack  (max 9 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Cmp
	TOKEN_BEGIN     AIR_ALPHA_ON_CLP
                dd      9       ; Number of Entries
	        REAL8  -180.0,  1.0
        	REAL8   -90.0,  0.3
	        REAL8   -18.0,  0.4
        	REAL8   -10.0,  0.6
	        REAL8     0.0,  1.0
        	REAL8    10.0,  0.6
	        REAL8    18.0,  0.4
        	REAL8    90.0,  0.3
	        REAL8   180.0,  1.0
        TOKEN_END

	;Scalar on CnBeta due to angle of attack  (max 9 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on CnBeta
	TOKEN_BEGIN     AIR_ALPHA_ON_CN_BETA
                dd      9       ; Number of Entries
	        REAL8  -180.0,  1.0
	        REAL8   -90.0,  0.0
	        REAL8   -18.0,  0.2
	        REAL8   -10.0,  0.3
	        REAL8     0.0,  1.0
	        REAL8    10.0,  0.3
	        REAL8    18.0,  0.2
	        REAL8    90.0,  0.0
	        REAL8   180.0,  1.0
        TOKEN_END

	;Scalar on Cnr due to angle of attack  (max 9 entries)
	; IN:  Angle of attack (degrees)
	; OUT: Scalar on Cnr
	TOKEN_BEGIN     AIR_ALPHA_ON_CNR
                dd      9       ; Number of Entries
	        REAL8  -180.0,  1.0
	        REAL8   -90.0,  0.1
	        REAL8   -18.0,  0.2
	        REAL8   -10.0,  0.4
	        REAL8     0.0,  1.0
	        REAL8    10.0,  0.4
	        REAL8    18.0,  0.2
	        REAL8    90.0,  0.1
	        REAL8   180.0,  1.0
        TOKEN_END

	;**** END OF ANGLE OF ATTACK TABLES ***************


	;**** START OF MACH TABLES ***************        

        	;Scalar on Lift due to mach (max 17 entries)
	;IN:  Mach
	;OUT: Scalar on CL0
	;DONE
        TOKEN_BEGIN     AIR_CL_MACH
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

	;Scalar on Drag due to mach (max 17 entries)
	;IN:  Mach
	;OUT: Delta CD0 due to mach
	TOKEN_BEGIN  AIR_10XPACK_CD0_MACH
	
		UINT32	17		;NUMBER OF ENTRIES
	               ;Mach   ;Delta CD0

	        REAL8   0.00,	0.0000
	        REAL8   0.20,	0.0000
	        REAL8   0.54,	0.0020
	        REAL8   0.66,	0.0034
	        REAL8   0.77,	0.0177
	        REAL8   0.84,	0.0203
	        REAL8   0.91,	0.0226
	        REAL8   0.97,	0.0243
	        REAL8   1.09,	0.0254
	        REAL8   1.32,	0.0251
	        REAL8   1.48,	0.0238
	        REAL8   1.73,	0.0170
	        REAL8   2.40,	0.0114
	        REAL8   2.60,	0.0101
	        REAL8   2.80,	0.0098
	        REAL8   3.00,	0.0098
	        REAL8   3.20,	0.0098

		TOKEN_END


	;**************************************************************************************
	; The following mach data tables are fixed size (17 elements) and are assumed to have
	; inputs of Mach from 0.0 to 3.2, where each table step is 0.2 Mach.  The output is 
	; an integer which is the scalar multiplied by 2^11, or 2048.  E.g. a desired about  of 
	; 0.25 would be configured in the table as 512.  All outputs are additive to the base
	; aerodynamic coefficient. 
	;**************************************************************************************

	;Integer mach table on Clde
	;IN:  Mach index (see Guidlines on Mach Integer Tables)
	;OUT: Delta Clde due to mach
	;DONE
        TOKEN_BEGIN     AIR_CL_DELTAE
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

	;Integer mach table on Cladot
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cladot due to mach
        TOKEN_BEGIN     AIR_CL_ADOT
	        dw          0           ;0.0    
	        dw          0           ;0.2    
	        dw        410           ;0.4    
	        dw       1024           ;0.6    
	        dw       2253           ;0.8    
	        dw       3482           ;1.0    
	        dw       2253           ;1.2    
	        dw       1024           ;1.4    
	        dw        410           ;1.6    
	        dw        410           ;1.8    
	        dw        410           ;2.0    
	        dw        410           ;2.2    
	        dw        410           ;2.4    
	        dw        410           ;2.6    
	        dw        410           ;2.8    
	        dw        410           ;3.0    
	        dw        410           ;3.2    
        TOKEN_END

        	;Integer mach table on CLq
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta CLq due to mach
TOKEN_BEGIN     AIR_CL_Q
	        dw          0           ;0.0    
	        dw          0           ;0.2    
	        dw       -410           ;0.4    
	        dw      -1024           ;0.6    
	        dw      -2458           ;0.8    
	        dw      -2458           ;1.0    
	        dw      -1024           ;1.2    
	        dw       -410           ;1.4    
	        dw          0           ;1.6    
	        dw          0           ;1.8    
	        dw          0           ;2.0    
	        dw          0           ;2.2    
	        dw          0           ;2.4    
	        dw          0           ;2.6    
	        dw          0           ;2.8    
	        dw          0           ;3.0    
	        dw          0           ;3.2    
        TOKEN_END

        ;Integer mach table on Clih
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Clih due to mach
        TOKEN_BEGIN     AIR_CL_IH
	        dw          0           ;0.0     
	        dw          0           ;0.2     
	        dw         20           ;0.4     
	        dw         82           ;0.6     
	        dw        328           ;0.8     
	        dw        328           ;1.0     
	        dw        328           ;1.2     
	        dw        328           ;1.4     
	        dw        328           ;1.6     
	        dw        328           ;1.8     
	        dw        328           ;2.0     
	        dw        328           ;2.2     
	        dw        328           ;2.4     
	        dw        328           ;2.6     
	        dw        328           ;2.8     
	        dw        328           ;3.0     
	        dw        328           ;3.2     
        TOKEN_END

        ;Integer mach table on Cmde
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cmde due to mach
	TOKEN_BEGIN     AIR_CM_DELTAE
	        dw          0           ;0.0     
	        dw        -20           ;0.2     
	        dw        -82           ;0.4     
	        dw       -163           ;0.6     
	        dw       -318           ;0.8     
	        dw       -207           ;1.0     
	        dw       -205           ;1.2     
	        dw       -102           ;1.4     
	        dw          0           ;1.6     
	        dw         51           ;1.8     
	        dw        102           ;2.0     
	        dw        102           ;2.2     
	        dw        102           ;2.4     
	        dw        102           ;2.6     
	        dw        102           ;2.8     
	        dw        102           ;3.0     
	        dw        102           ;3.2     
        TOKEN_END

	;Integer mach table on Cmadot
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cmadot due to mach
        TOKEN_BEGIN     AIR_CM_ADOT
	        dw          0           ;0.0     
	        dw         51           ;0.2     
	        dw        205           ;0.4     
	        dw        563           ;0.6     
	        dw       1536           ;0.8     
	        dw       2048           ;1.0     
	        dw          0           ;1.2     
	        dw      -6144           ;1.4     
	        dw      -8192           ;1.6     
	        dw      -9216           ;1.8     
	        dw     -10240           ;2.0     
	        dw     -10240           ;2.2     
	        dw     -10240           ;2.4     
	        dw     -10240           ;2.6     
	        dw     -10240           ;2.8     
	        dw     -10240           ;3.0     
	        dw     -10240           ;3.2     
        TOKEN_END

 	;Integer mach table on Cmq
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cmq due to mach
	;DONE
        TOKEN_BEGIN     AIR_CM_Q
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

        ;Integer mach table on Cmih
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cmih due to mach
	TOKEN_BEGIN     AIR_CM_IH
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


       	;Integer mach table on Cm0
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cm0 due to mach
	;DONE
	TOKEN_BEGIN     AIR_CMO
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

        ;Integer mach table on Cyb
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cyb due to mach
	TOKEN_BEGIN     AIR_CY_BETA
	        dw          0           ;0.0            
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;Integer mach table on Cydr
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cydr due to mach
        TOKEN_BEGIN     AIR_CY_DELTAR
	        dw          0           ;0.0             
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw        -10           ;0.8
	        dw        -10           ;1.0
	        dw        -10           ;1.2
	        dw        -10           ;1.4
	        dw        -10           ;1.6
	        dw        -10           ;1.8
	        dw        -10           ;2.0
	        dw        -10           ;2.2
	        dw        -10           ;2.4
	        dw        -10           ;2.6
	        dw        -10           ;2.8
	        dw        -10           ;3.0
	        dw        -10           ;3.2
        TOKEN_END

	;Integer mach table on Cyr
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cyr due to mach
        TOKEN_BEGIN     AIR_CY_R
	        dw          0           ;0.0             
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;Integer mach table on Cyp
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cyp due to mach
        TOKEN_BEGIN     AIR_CY_P
	        dw          0           ;0.0             
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;Integer mach table on Clb
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Clb due to mach
        TOKEN_BEGIN     AIR_CL_BETA
	        dw          0           ;0.0            
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END


	;Integer mach table on Cldr
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cldr due to mach
        TOKEN_BEGIN     AIR_CL_DELTAR
	        dw          0           ;0.0             
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;Integer mach table on Clda
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Clda due to mach
        TOKEN_BEGIN     AIR_CL_DELTAA
	        dw          0           ;0.0             
	        dw          0           ;0.2
	        dw        -10           ;0.4
	        dw        -21           ;0.6
	        dw        -41           ;0.8
	        dw        -51           ;1.0
	        dw        -51           ;1.2
	        dw        -51           ;1.4
	        dw        -51           ;1.6
	        dw        -51           ;1.8
	        dw        -51           ;2.0
	        dw        -51           ;2.2
	        dw        -51           ;2.4
	        dw        -51           ;2.6
	        dw        -51           ;2.8
	        dw        -51           ;3.0
	        dw        -51           ;3.2
        TOKEN_END

	;Integer mach table on Clr
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Clr due to mach
        TOKEN_BEGIN     AIR_CL_R
	        dw          0           ;0.0            
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;Integer mach table on Clp
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Clp due to mach
        TOKEN_BEGIN     AIR_CL_P
	        dw          0           ;0.0            
	        dw        -10           ;0.2
	        dw        -41           ;0.4
	        dw       -102           ;0.6
	        dw       -205           ;0.8
	        dw       -225           ;1.0
	        dw       -225           ;1.2
	        dw       -225           ;1.4
	        dw       -225           ;1.6
	        dw       -225           ;1.8
	        dw       -225           ;2.0
	        dw       -225           ;2.2
	        dw       -225           ;2.4
	        dw       -225           ;2.6
	        dw       -225           ;2.8
	        dw       -225           ;3.0
	        dw       -225           ;3.2
        TOKEN_END


	;Integer mach table on Cnb
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cnb due to mach
        TOKEN_BEGIN     AIR_CN_BETA
	        dw          0           ;0.0             
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;Integer mach table on Cndr
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cndr due to mach
        TOKEN_BEGIN     AIR_CN_DELTAR
	        dw          0           ;0.0            
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;Integer mach table on Cnda
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cnda due to mach
        TOKEN_BEGIN     AIR_CN_DELTAA
	        dw          0           ;0.0             
	        dw          0           ;0.2
	        dw         -2           ;0.4
	        dw         -4           ;0.6
	        dw         -6           ;0.8
	        dw         -6           ;1.0
	        dw         -6           ;1.2
	        dw         -6           ;1.4
	        dw         -6           ;1.6
	        dw         -6           ;1.8
	        dw         -6           ;2.0
	        dw         -6           ;2.2
	        dw         -6           ;2.4
	        dw         -6           ;2.6
	        dw         -6           ;2.8
	        dw         -6           ;3.0
	        dw         -6           ;3.2
        TOKEN_END

	;Integer mach table on Cnr
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cnr due to mach
        TOKEN_BEGIN     AIR_CN_R
	        dw          0           ;0.0            -
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END


	;Integer mach table on Cnp 
	;IN:  Mach index  (see Guidlines on Mach Integer Tables)
	;OUT: Delta Cnp due to mach
        TOKEN_BEGIN     AIR_CN_P
	        dw          0           ;0.0 
	        dw          0           ;0.2
	        dw          0           ;0.4
	        dw          0           ;0.6
	        dw          0           ;0.8
	        dw          0           ;1.0
	        dw          0           ;1.2
	        dw          0           ;1.4
	        dw          0           ;1.6
	        dw          0           ;1.8
	        dw          0           ;2.0
	        dw          0           ;2.2
	        dw          0           ;2.4
	        dw          0           ;2.6
	        dw          0           ;2.8
	        dw          0           ;3.0
	        dw          0           ;3.2
        TOKEN_END

	;**** END OF MACH TABLES *********************************


	;***END OF AERODYNAMICS**********************************************************************************************
	;********************************************************************************************************************




	;********************************************************************************************************************
	;****START OF ENGINE DATA *******************************************************************************************

	

	;Commanded N2 (corrected) vs. Throttle table at 0 Mach (max 9 rows, 11 columns)
	;NOTE:  The specific (low) Mach value is specified at the 0,0 position of the table
        ;	This table is used in conjunction with the AIR_70_MACH_HI_CORRECTED_COMMANDED_NE table

        ;IN: X: 1/atmospheric press ratio (Psl/P)(note: use inverse of delta pressure ratio so that values are in increasing order)
        ;IN: Y: %Power Lever / Throttle  
        ;OUT: Corrected N2 for MACH = 0
	TOKEN_BEGIN     AIR_70_MACH_0_CORRECTED_COMMANDED_NE

        UINT32 9,3
        ;               %PL        0'       70K'
        REAL8           0.00,    1.00 ,    22.57 ; Pressure Ratio (Psl/P)
        REAL8           0.00,    66.00,    82.50
        REAL8           0.42,    78.80,    95.40
        REAL8           0.51,    82.50,    98.50
        REAL8           0.61,    87.40,   101.10
        REAL8           0.70,    92.00,   103.10
        REAL8           0.79,    96.20,   105.70
        REAL8           0.93,   103.10,   108.06
        REAL8           1.00,   105.00,   108.06
        TOKEN_END


	;Commanded N2 (corrected) vs. Throttle table at HI Mach (max 9 rows, 11 columns)
	;NOTE:  The specific (HI) Mach value is specified at the 0,0 position of the table
        ;	This table is used in conjunction with the AIR_70_MACH_0_CORRECTED_COMMANDED_NE table

        ;IN: X: 1/atmospheric press ratio (Psl/P)(note: use inverse of delta pressure ratio so that values are in increasing order)
        ;IN: Y: %Power Lever / Throttle  
        ;OUT: Corrected N2 for specified MACH 
        TOKEN_BEGIN     AIR_70_MACH_HI_CORRECTED_COMMANDED_NE

        UINT32 9,3
        ;               %PL       0'       70K'
        REAL8           0.90,    1.00 ,   22.57 ; Pressure Ratio (Psl/P)
        REAL8           0.00,    62.00,   82.50
        REAL8           0.42,    77.00,   95.40
        REAL8           0.51,    80.20,   98.50
        REAL8           0.61,    84.80,   101.10
        REAL8           0.70,    89.10,   103.10
        REAL8           0.79,    92.20,   105.70
        REAL8           0.93,    96.00,   108.06
        REAL8           1.00,    98.20,   108.06

        TOKEN_END


	;N2 (Corrected) vs. FuelFlow constant
	;  where the constant is a normalized ratio of actual fuelflow parameter to static thrust
	;IN:  Normalized Fuelflow constant
	;OUT: N2 (corrected)
        TOKEN_BEGIN     AIR_70_CORRECTED_N2_FROM_FF

        UINT32 10

        REAL8   0.00000,       0.0  
        REAL8   0.00294,      10.0
        REAL8   0.01180,      30.0
        REAL8   0.02066,      40.0
        REAL8   0.03397,      50.0
        REAL8   0.05317,      60.0
        REAL8   0.13391,      80.0
        REAL8   0.25771,      90.0
        REAL8   0.54000,     100.0
        REAL8   0.68686,     105.0

        TOKEN_END

	;N1 vs N2 & Mach lookup table (max 13 rows, 11 columns)
	;IN: X:  Mach
	;IN: Y:  N2 (corrected)
	;OUT: N1 (corrected)	
	TOKEN_BEGIN     AIR_70_N2_TO_N1_TABLE

        UINT32  13,3    ;rows,cols
                  ;N2
        REAL8     0.0,     0.0,    0.9 ; Mach
        REAL8     0.0,     0.0,    0.0
        REAL8    10.0,     2.0,   12.0
        REAL8    20.0,     7.0,   22.5
        REAL8    30.0,    10.2,   32.0
        REAL8    40.0,    15.1,   41.2
        REAL8    50.0,    20.1,   47.0
        REAL8    60.0,    28.0,   52.5
        REAL8    70.0,    38.0,   57.0
        REAL8    80.0,    50.0,   67.5
        REAL8    90.0,    70.0,   80.8
        REAL8   100.0,    89.4,  100.8
        REAL8   110.0,   112.0,  120.0

        TOKEN_END


	;N1 vs Thrust table (max 21 rows, 11 columns)
	;IN: X: Mach
	;IN: Y: N1 (corrected)
	;OUT: Gross Thurst (corrected) / static thrust
        TOKEN_BEGIN     AIR_70_N1_AND_MACH_ON_THRUST

        UINT32 21,3     ;ROWS,COLS
	;        N1
        REAL8    0.0,      0.0,        0.9 ; Mach
        REAL8    0.0,  0.00000,    0.00000
        REAL8   20.0,  0.02540,    0.07409
        REAL8   25.0,  0.05080,    0.15929
        REAL8   30.0,  0.07983,    0.25563
        REAL8   35.0,  0.11249,    0.34829
        REAL8   40.0,  0.20000,    0.44457
        REAL8   45.0,  0.28100,    0.54086
        REAL8   50.0,  0.36800,    0.70600
        REAL8   55.0,  0.44500,    0.84400
        REAL8   60.0,  0.52100,    0.99700
        REAL8   65.0,  0.62900,    1.15500
        REAL8   70.0,  0.72600,    1.32400
        REAL8   75.0,  0.81800,    1.57500
        REAL8   80.0,  0.90000,    1.77400
        REAL8   85.0,  0.99200,    1.95300
        REAL8   90.0,  1.04300,    2.05500
        REAL8   95.0,  1.06900,    2.15700
        REAL8  100.0,  1.12500,    2.24400
        REAL8  105.0,  1.14500,    2.27500
        REAL8  110.0,  1.17000,    2.31600

        TOKEN_END

	;N1 vs AirFlow/Ram Drag   (max 21 rows, 11 columns)
	;IN: X:  Mach
	;IN: Y:  N1 (corrected)
	;OUT: Normalized Airflow (Corrected) = Airflow / inlet area
        TOKEN_BEGIN     AIR_70_CORRECTED_AIRFLOW
        
        UINT32  21,3
	;	 N1
        REAL8    0.0,    0.0,         0.9    ; Mach
        REAL8    0.0,    0.00000,     0.00000
        REAL8   20.0,    4.28954,    14.08090
        REAL8   25.0,    6.06131,    15.15328
        REAL8   30.0,    7.80977,    16.31892
        REAL8   35.0,    9.58154,    17.50787
        REAL8   40.0,   11.32999,    18.62688
        REAL8   45.0,   13.14839,    19.79252
        REAL8   50.0,   14.87353,    20.91153
        REAL8   55.0,   16.62198,    21.98391
        REAL8   60.0,   18.39375,    23.14955
        REAL8   65.0,   20.02564,    24.22194
        REAL8   70.0,   21.84404,    25.34095
        REAL8   75.0,   23.66243,    26.39002
        REAL8   80.0,   25.62070,    27.76547
        REAL8   85.0,   27.83541,    29.16424
        REAL8   90.0,   30.25994,    30.58632
        REAL8   95.0,   32.12496,    32.00839
        REAL8  100.0,   33.59366,    33.17403
        REAL8  105.0,   34.71267,    34.12985
        REAL8  110.0,   35.29549,    35.22555
        TOKEN_END


	;Afterburner on thrust table (max 10 entries)
	;IN:  Mach
	;OUT: Scalar on Thrust for max afterburner.  
        ;     Output is scaled by percent afterburner active
	TOKEN_BEGIN	AIR_70_AFTERBURNER_ON_THRUST_TABLE

	UINT32 6	;Entries

	REAL8	0.0,    1.58 
	REAL8	0.4,    1.69 
	REAL8	0.8,    1.80 
	REAL8	1.2,    1.84 
	REAL8	1.6,    1.85 
	REAL8	2.0,    1.85 

 	TOKEN_END



        ;Dynamic primary exhaust nozzle available flag
        TOKEN_BEGIN     AIR_70_PRIMARY_NOZZLE
	        BOOL  FALSE 	;fVariablePrimaryNozzle
        TOKEN_END



	;Nozzle animation table and afterburner offset (if primary nozzle available)
	; The output is the percent open of the primary nozzle (max 1.0)
	TOKEN_BEGIN	AIR_10XPACK_N1_MACH_ON_NOZZLE

        FLOAT32 0.30 ;Offset due to afterburner state

	;Exhaust nozzle table  (max 4 rows, 3 columns)
	;IN:  X: mach, 
	;IN:  Y: Corrected N1
	;OUT: Primary Nozzle Pct open
	UINT32 4,3	;ROWS,COLS
                 ;N1     M-lo   M-hi
        REAL8    0.00,  0.80,   1.05 
        REAL8   40.00,  0.55,   0.80 
        REAL8   65.00,  0.62,   0.85
        REAL8   96.00,  0.70,   0.90         
	TOKEN_END	




	;Thrust reverser flags
        TOKEN_BEGIN     AIR_70_REVERSER_NOZZLE
               BOOL  TRUE	;fReverserNozzle
	       BOOL  FALSE      ;fMachControlledReverserNozzle
        TOKEN_END


	;Engine Pressure Ratio        
        TOKEN_BEGIN     AIR_70_EPR
	    REAL8 1.0		;EPR tuning constant 
	    REAL8 1.4		;Max EPR             
	    REAL8 14.0		;EPR time constant             
        TOKEN_END

        

	;Oil Temperature
        TOKEN_BEGIN     AIR_61S_OIL_TEMPERATURE
                REAL8   1.000000        ; Oil temp tuning constant
                REAL8   0.000000        ; Oil temp cooling constant
                REAL8   600.000000      ; Max Oil Temp (deg Rankine)
                REAL8   0.010000        ; Oil temp time constant
        TOKEN_END

	;Oil Pressure
        TOKEN_BEGIN     AIR_61S_OIL_PRESSURE
                REAL8   1.000000        ; Oil pressure tuning constant
                REAL8   19440.000000    ; Oil pressure max (PSF)
                REAL8   0.800000        ; Oil pressure time constant
        TOKEN_END


	;Interstage turbine temperature
        TOKEN_BEGIN     AIR_70_ITT
		REAL8 	1.0 		;ITT tuning constant
		REAL8 	2400.0  	;ITT peak temperature
                REAL8 	2.0 		;ITT time constant
        TOKEN_END
       

        ;Exhaust Gas Temperature
        TOKEN_BEGIN     AIR_61S_EGT
                REAL8   1.000000        ; EGT tuning constant
                REAL8   1285.000000     ; EGT peak temperature (typical peak: 1200 degF + 460)
                REAL8   2.000000        ; EGT time constant
        TOKEN_END

	;**** PID CONTROLLERS *******************************************************
	;The following PID controllers are utilized only by computer controlled (AI) aircraft system for heading and airspeed control
        TOKEN_BEGIN     AIR_AP_PID_CONTROLLERSF
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <1.8,      0.0,      0.0,      1.5,      2.0,      0.0,      20.0>      ; head_hold pid_p, i, i2, d, i_boundary, i2_boundary, d_boundary
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.35,     0.002,    0.0,      8.5,      10.0,     0.0,      80.0>      ; airspeed_hold pid_p, i, i2, d, i_boundary, i2_boundary, d_boundary
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
                AIRFILE_PID     <0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000>  ; UNUSED
        TOKEN_END

sim_size        equ     $ - sim_data

        end

