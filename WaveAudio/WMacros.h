#pragma once
#if !defined(_WMACROS_H_)
#	define	_WMACROS_H_

	// >= unsafe use of type bool in operation
	#pragma warning(disable: 4804)

	enum ControlTypes : WORD
	{
		UNKNOWN = 0,
		BUTTON = 1,
		EDIT = 2,
		LABEL = 3,
		SPINNER = 4,
		PROGRESSBAR = 5
	};

	#	define	AUDIO_ERROR_BUFFER_MAX_SIZE							256
	#	define	AT_BITS_PER_SAMPLE_08								0x0010
	#	define	AT_BITS_PER_SAMPLE_16								0x0020
	#	define	AT_BITS_PER_SAMPLE_24								0x0030

	#	define	AT_FCY_SAMPLES_PER_SECONDS_22050					0x005622
	#	define	AT_FCY_SAMPLES_PER_SECONDS_44100					0x00AC44
	
	#	define	MAX_CONTROLS_TYPES_PER_WINDOW						5
	#	define	MAX_CONTROLS_PER_WINDOW								5
	#	define	MAX_BUFFER_SIZE										256
	#	define	MAX_CLASS_NAME_BUFFER_SIZE							50
	#	define	MAX_WINDOW_NAME_BUFFER_SIZE							50
	#	define	MAX_ERROR_BUFFER_SIZE								128

	#if !(defined(VALIDATE_CTRL_TYPE))
	#	define VALIDATE_CTRL_TYPE(ControlId, ControlTypeId)			(((ControlId > 0) && ((ControlTypeId <= MAX_CONTROLS_TYPES_PER_WINDOW) && ((ControlTypeId % (MAX_CONTROLS_TYPES_PER_WINDOW + 1))) > 0) && \
																	(ControlId % (ControlTypeId * MAX_CONTROLS_PER_WINDOW))) >= 0)
	#endif

	#if !(defined(GET_CTRL_TYPE_ID))
	#	define GET_CTRL_TYPE_INDEX(ControlId, ControlTypeId)		((VALIDATE_CTRL_TYPE(ControlId, ControlTypeId)) ? \
																	(ControlId % (ControlTypeId * MAX_CONTROLS_PER_WINDOW)) : -1) 
	#endif

	#if	(!defined(COMPARE_CONTROL_TYPE))
	#	define COMPARE_CONTROL_TYPE(TypeName, StringType, ControlType)		\
																	if (!TypeName.compare(StringType)) \
																	{ \
																	return ControlType; \
																	}
	#endif 
	
	#if (!defined(BEGIN_VALIDATE_WINDOW_CONTROL_TYPE))
	#	define BEGIN_VALIDATE_WINDOW_CONTROL_TYPE(WindowHandler, ControlIdVarName, ControlId)	\
																	DWORD ControlIdVarName = ControlId; \
																	ControlTypes controType = Window_t::GetControlType(hWnd, ControlIdVarName); \
																	if (controType != ControlTypes::UNKNOWN) \
																	{ \

	#endif

	#if (!defined(END_VALIDATE_WINDOW_CONTROL_TYPE))
	#	define	END_VALIDATE_WINDOW_CONTROL_TYPE					}
	#endif

	#if (!defined(FREE_NEW))
	#	define	FREE_MEMORY_WITH_NEW(pointer)						if (pointer) {delete pointer; pointer = nullptr};
	#endif

	#	define	IDT_ELAPSED_SECOND_TICK								WM_USER + 999

	#	define BEGIN_BUTTON_CONTROL									(ControlTypes::BUTTON		*	MAX_CONTROLS_PER_WINDOW)
	#	define BEGIN_EDIT_CONTROL									(ControlTypes::EDIT			*	MAX_CONTROLS_PER_WINDOW)
	#	define BEGIN_LABEL_CONTROL									(ControlTypes::LABEL		*	MAX_CONTROLS_PER_WINDOW)
	#	define BEGIN_SPINNER_CONTROL								(ControlTypes::SPINNER		*	MAX_CONTROLS_PER_WINDOW)
	#	define BEGIN_PROGRESSBAR_CONTROL							(ControlTypes::PROGRESSBAR	*	MAX_CONTROLS_PER_WINDOW)

	#	define	ID_BTN_PROCESS										BEGIN_BUTTON_CONTROL		
	#	define	ID_BTN_SEARCH_FOLDER								BEGIN_BUTTON_CONTROL		+ 1
	#	define	ID_EDIT_FOLDERNAME									BEGIN_EDIT_CONTROL			
	#	define	ID_EDIT_FILENAME									BEGIN_EDIT_CONTROL			+ 1
	#	define	ID_EDIT_RECORD_TIME									BEGIN_EDIT_CONTROL			+ 2
	#	define	ID_LABEL_FILENAME									BEGIN_LABEL_CONTROL			
	#	define	ID_LABEL_FOLDERNAME									BEGIN_LABEL_CONTROL			+ 1
	#	define	ID_LABEL_SPINNER									BEGIN_LABEL_CONTROL			+ 2
	#	define	ID_LABEL_PROGRESSBAR								BEGIN_LABEL_CONTROL			+ 3
	#	define	ID_SPINNER_RECORD_TIME								BEGIN_SPINNER_CONTROL		
	#	define	ID_PB_PROGRESS										BEGIN_PROGRESSBAR_CONTROL
#endif 



