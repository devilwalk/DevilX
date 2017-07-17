#pragma once
namespace NSDevilX
{
	namespace NSInputSystem
	{
		class IEnum
		{
		public:
			enum EPhysicalDeviceType
			{
				EPhysicalDeviceType_Mouse,
				EPhysicalDeviceType_Keyboard
			};
			enum EButtonState
			{
				EButtonState_Unknown,
				EButtonState_Released,
				EButtonState_Pressed
			};
			enum EMouseAxisType
			{
				EMouseAxisType_X,
				EMouseAxisType_Y,
				EMouseAxisType_Z
			};
			enum EMouseButtonType
			{
				EMouseButtonType_Left,
				EMouseButtonType_Right,
				EMouseButtonType_Middle,
				EMouseButtonType_Last=EMouseButtonType_Middle
			};
			enum EKeyType
			{
				EKeyType_ESCAPE=0x01,
				EKeyType_1=0x02,
				EKeyType_2=0x03,
				EKeyType_3=0x04,
				EKeyType_4=0x05,
				EKeyType_5=0x06,
				EKeyType_6=0x07,
				EKeyType_7=0x08,
				EKeyType_8=0x09,
				EKeyType_9=0x0A,
				EKeyType_0=0x0B,
				EKeyType_MINUS=0x0C,    /* - on main keyboard */
				EKeyType_EQUALS=0x0D,
				EKeyType_BACK=0x0E,    /* backspace */
				EKeyType_TAB=0x0F,
				EKeyType_Q=0x10,
				EKeyType_W=0x11,
				EKeyType_E=0x12,
				EKeyType_R=0x13,
				EKeyType_T=0x14,
				EKeyType_Y=0x15,
				EKeyType_U=0x16,
				EKeyType_I=0x17,
				EKeyType_O=0x18,
				EKeyType_P=0x19,
				EKeyType_LBRACKET=0x1A,
				EKeyType_RBRACKET=0x1B,
				EKeyType_RETURN=0x1C,    /* Enter on main keyboard */
				EKeyType_LCONTROL=0x1D,
				EKeyType_A=0x1E,
				EKeyType_S=0x1F,
				EKeyType_D=0x20,
				EKeyType_F=0x21,
				EKeyType_G=0x22,
				EKeyType_H=0x23,
				EKeyType_J=0x24,
				EKeyType_K=0x25,
				EKeyType_L=0x26,
				EKeyType_SEMICOLON=0x27,
				EKeyType_APOSTROPHE=0x28,
				EKeyType_GRAVE=0x29,    /* accent grave */
				EKeyType_LSHIFT=0x2A,
				EKeyType_BACKSLASH=0x2B,
				EKeyType_Z=0x2C,
				EKeyType_X=0x2D,
				EKeyType_C=0x2E,
				EKeyType_V=0x2F,
				EKeyType_B=0x30,
				EKeyType_N=0x31,
				EKeyType_M=0x32,
				EKeyType_COMMA=0x33,
				EKeyType_PERIOD=0x34,    /* . on main keyboard */
				EKeyType_SLASH=0x35,    /* / on main keyboard */
				EKeyType_RSHIFT=0x36,
				EKeyType_MULTIPLY=0x37,    /* * on numeric keypad */
				EKeyType_LMENU=0x38,    /* left Alt */
				EKeyType_SPACE=0x39,
				EKeyType_CAPITAL=0x3A,
				EKeyType_F1=0x3B,
				EKeyType_F2=0x3C,
				EKeyType_F3=0x3D,
				EKeyType_F4=0x3E,
				EKeyType_F5=0x3F,
				EKeyType_F6=0x40,
				EKeyType_F7=0x41,
				EKeyType_F8=0x42,
				EKeyType_F9=0x43,
				EKeyType_F10=0x44,
				EKeyType_NUMLOCK=0x45,
				EKeyType_SCROLL=0x46,    /* Scroll Lock */
				EKeyType_NUMPAD7=0x47,
				EKeyType_NUMPAD8=0x48,
				EKeyType_NUMPAD9=0x49,
				EKeyType_SUBTRACT=0x4A,    /* - on numeric keypad */
				EKeyType_NUMPAD4=0x4B,
				EKeyType_NUMPAD5=0x4C,
				EKeyType_NUMPAD6=0x4D,
				EKeyType_ADD=0x4E,    /* + on numeric keypad */
				EKeyType_NUMPAD1=0x4F,
				EKeyType_NUMPAD2=0x50,
				EKeyType_NUMPAD3=0x51,
				EKeyType_NUMPAD0=0x52,
				EKeyType_DECIMAL=0x53,    /* . on numeric keypad */
				EKeyType_OEM_102=0x56,    /* <> or \| on RT 102-key keyboard (Non-U.S.) */
				EKeyType_F11=0x57,
				EKeyType_F12=0x58,
				EKeyType_F13=0x64,    /*                     (NEC PC98) */
				EKeyType_F14=0x65,    /*                     (NEC PC98) */
				EKeyType_F15=0x66,    /*                     (NEC PC98) */
				EKeyType_KANA=0x70,    /* (Japanese keyboard)            */
				EKeyType_ABNT_C1=0x73,    /* /? on Brazilian keyboard */
				EKeyType_CONVERT=0x79,    /* (Japanese keyboard)            */
				EKeyType_NOCONVERT=0x7B,    /* (Japanese keyboard)            */
				EKeyType_YEN=0x7D,    /* (Japanese keyboard)            */
				EKeyType_ABNT_C2=0x7E,    /* Numpad . on Brazilian keyboard */
				EKeyType_NUMPADEQUALS=0x8D,    /* = on numeric keypad (NEC PC98) */
				EKeyType_PREVTRACK=0x90,    /* Previous Track (EKeyType_CIRCUMFLEX on Japanese keyboard) */
				EKeyType_AT=0x91,    /*                     (NEC PC98) */
				EKeyType_COLON=0x92,    /*                     (NEC PC98) */
				EKeyType_UNDERLINE=0x93,    /*                     (NEC PC98) */
				EKeyType_KANJI=0x94,    /* (Japanese keyboard)            */
				EKeyType_STOP=0x95,    /*                     (NEC PC98) */
				EKeyType_AX=0x96,    /*                     (Japan AX) */
				EKeyType_UNLABELED=0x97,    /*                        (J3100) */
				EKeyType_NEXTTRACK=0x99,    /* Next Track */
				EKeyType_NUMPADENTER=0x9C,    /* Enter on numeric keypad */
				EKeyType_RCONTROL=0x9D,
				EKeyType_MUTE=0xA0,    /* Mute */
				EKeyType_CALCULATOR=0xA1,    /* Calculator */
				EKeyType_PLAYPAUSE=0xA2,    /* Play / Pause */
				EKeyType_MEDIASTOP=0xA4,    /* Media Stop */
				EKeyType_VOLUMEDOWN=0xAE,    /* Volume - */
				EKeyType_VOLUMEUP=0xB0,    /* Volume + */
				EKeyType_WEBHOME=0xB2,    /* Web home */
				EKeyType_NUMPADCOMMA=0xB3,    /* , on numeric keypad (NEC PC98) */
				EKeyType_DIVIDE=0xB5,    /* / on numeric keypad */
				EKeyType_SYSRQ=0xB7,
				EKeyType_RMENU=0xB8,    /* right Alt */
				EKeyType_PAUSE=0xC5,    /* Pause */
				EKeyType_HOME=0xC7,    /* Home on arrow keypad */
				EKeyType_UP=0xC8,    /* UpArrow on arrow keypad */
				EKeyType_PRIOR=0xC9,    /* PgUp on arrow keypad */
				EKeyType_LEFT=0xCB,    /* LeftArrow on arrow keypad */
				EKeyType_RIGHT=0xCD,    /* RightArrow on arrow keypad */
				EKeyType_END=0xCF,    /* End on arrow keypad */
				EKeyType_DOWN=0xD0,    /* DownArrow on arrow keypad */
				EKeyType_NEXT=0xD1,    /* PgDn on arrow keypad */
				EKeyType_INSERT=0xD2,    /* Insert on arrow keypad */
				EKeyType_DELETE=0xD3,    /* Delete on arrow keypad */
				EKeyType_LWIN=0xDB,    /* Left Windows key */
				EKeyType_RWIN=0xDC,    /* Right Windows key */
				EKeyType_APPS=0xDD,    /* AppMenu key */
				EKeyType_POWER=0xDE,    /* System Power */
				EKeyType_SLEEP=0xDF,    /* System Sleep */
				EKeyType_WAKE=0xE3,    /* System Wake */
				EKeyType_WEBSEARCH=0xE5,    /* Web Search */
				EKeyType_WEBFAVORITES=0xE6,    /* Web Favorites */
				EKeyType_WEBREFRESH=0xE7,    /* Web Refresh */
				EKeyType_WEBSTOP=0xE8,    /* Web Stop */
				EKeyType_WEBFORWARD=0xE9,    /* Web Forward */
				EKeyType_WEBBACK=0xEA,    /* Web Back */
				EKeyType_MYCOMPUTER=0xEB,    /* My Computer */
				EKeyType_MAIL=0xEC,    /* Mail */
				EKeyType_MEDIASELECT=0xED,    /* Media Select */
				EKeyType_Last=EKeyType_MEDIASELECT,

				/*
				*  Alternate names for keys, to facilitate transition from DOS.
				*/
				EKeyType_BACKSPACE=EKeyType_BACK,            /* backspace */
				EKeyType_NUMPADSTAR=EKeyType_MULTIPLY,        /* * on numeric keypad */
				EKeyType_LALT=EKeyType_LMENU,           /* left Alt */
				EKeyType_CAPSLOCK=EKeyType_CAPITAL,         /* CapsLock */
				EKeyType_NUMPADMINUS=EKeyType_SUBTRACT,        /* - on numeric keypad */
				EKeyType_NUMPADPLUS=EKeyType_ADD,             /* + on numeric keypad */
				EKeyType_NUMPADPERIOD=EKeyType_DECIMAL,         /* . on numeric keypad */
				EKeyType_NUMPADSLASH=EKeyType_DIVIDE,          /* / on numeric keypad */
				EKeyType_RALT=EKeyType_RMENU,           /* right Alt */
				EKeyType_UPARROW=EKeyType_UP,              /* UpArrow on arrow keypad */
				EKeyType_PGUP=EKeyType_PRIOR,           /* PgUp on arrow keypad */
				EKeyType_LEFTARROW=EKeyType_LEFT,            /* LeftArrow on arrow keypad */
				EKeyType_RIGHTARROW=EKeyType_RIGHT,           /* RightArrow on arrow keypad */
				EKeyType_DOWNARROW=EKeyType_DOWN,            /* DownArrow on arrow keypad */
				EKeyType_PGDN=EKeyType_NEXT,            /* PgDn on arrow keypad */

								/*
								*  Alternate names for keys originally not used on US keyboards.
								*/
				EKeyType_CIRCUMFLEX=EKeyType_PREVTRACK       /* Japanese keyboard */
			};
			enum EMouseEventType
			{
				EMouseEventType_Move,
				EMouseEventType_ButtonDown,
				EMouseEventType_ButtonUp
			};
		};
	}
}