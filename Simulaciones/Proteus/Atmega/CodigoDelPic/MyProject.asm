
_Alarma:

	MOVF       _res6+0, 0
	MOVWF      FARG_Sound_Play_freq_in_hz+0
	MOVF       _res6+1, 0
	MOVWF      FARG_Sound_Play_freq_in_hz+1
	MOVF       _blanca+0, 0
	MOVWF      FARG_Sound_Play_duration_ms+0
	MOVF       _blanca+1, 0
	MOVWF      FARG_Sound_Play_duration_ms+1
	CALL       _Sound_Play+0
	MOVF       _mi6+0, 0
	MOVWF      FARG_Sound_Play_freq_in_hz+0
	MOVF       _mi6+1, 0
	MOVWF      FARG_Sound_Play_freq_in_hz+1
	MOVF       _blanca+0, 0
	MOVWF      FARG_Sound_Play_duration_ms+0
	MOVF       _blanca+1, 0
	MOVWF      FARG_Sound_Play_duration_ms+1
	CALL       _Sound_Play+0
L_end_Alarma:
	RETURN
; end of _Alarma

_main:

	CLRF       ANSEL+0
	CLRF       ANSELH+0
	BCF        C1ON_bit+0, BitPos(C1ON_bit+0)
	BCF        C2ON_bit+0, BitPos(C2ON_bit+0)
	MOVLW      248
	MOVWF      TRISB+0
	MOVLW      PORTC+0
	MOVWF      FARG_Sound_Init_snd_port+0
	MOVLW      3
	MOVWF      FARG_Sound_Init_snd_pin+0
	CALL       _Sound_Init+0
L_main0:
	MOVLW      PORTB+0
	MOVWF      FARG_Button_port+0
	MOVLW      3
	MOVWF      FARG_Button_pin+0
	MOVLW      1
	MOVWF      FARG_Button_time_ms+0
	MOVLW      1
	MOVWF      FARG_Button_active_state+0
	CALL       _Button+0
	MOVF       R0+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main2
	CALL       _Alarma+0
L_main2:
	MOVLW      2
	MOVWF      R11+0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      186
	MOVWF      R13+0
L_main3:
	DECFSZ     R13+0, 1
	GOTO       L_main3
	DECFSZ     R12+0, 1
	GOTO       L_main3
	DECFSZ     R11+0, 1
	GOTO       L_main3
	NOP
	MOVLW      PORTB+0
	MOVWF      FARG_Button_port+0
	MOVLW      4
	MOVWF      FARG_Button_pin+0
	MOVLW      1
	MOVWF      FARG_Button_time_ms+0
	MOVLW      1
	MOVWF      FARG_Button_active_state+0
	CALL       _Button+0
	MOVF       R0+0, 0
	BTFSC      STATUS+0, 2
	GOTO       L_main4
	MOVLW      2
	MOVWF      R11+0
	MOVLW      4
	MOVWF      R12+0
	MOVLW      186
	MOVWF      R13+0
L_main5:
	DECFSZ     R13+0, 1
	GOTO       L_main5
	DECFSZ     R12+0, 1
	GOTO       L_main5
	DECFSZ     R11+0, 1
	GOTO       L_main5
	NOP
L_main4:
	GOTO       L_main0
L_end_main:
	GOTO       $+0
; end of _main
