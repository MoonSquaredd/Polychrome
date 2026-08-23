Polychrome Api
==============

All definitions of Polychrome's Api.

Types
-----
`struct <https://en.cppreference.com/c/language/struct>`_ **PC_Color8**
_______________________________________________________________________
A struct representing a color in RGBA format.

`uint8_t <https://en.cppreference.com/c/types/integer>`_ **r** = ``0``;
 - The color's red component, ranging from 0 to 255.

`uint8_t <https://en.cppreference.com/c/types/integer>`_ **g** = ``0``;
 - The color's green component, ranging from 0 to 255.

`uint8_t <https://en.cppreference.com/c/types/integer>`_ **b** = ``0``;
 - The color's blue component, ranging from 0 to 255.

`uint8_t <https://en.cppreference.com/c/types/integer>`_ **a** = ``255``;
 - The color's alpha component, ranging from 0 to 255. A value of 0 means a fully transparent color. A value of 255 means a fully opaque color.

.. note::

    Some game-defined colors might ignore alpha completely.

`struct <https://en.cppreference.com/c/language/struct>`_ **PC_Color**
_______________________________________________________________________
A variation of PC_Color8 using floats instead of integers.

`float <https://cppreference.com/c/language/type>`_ **r** = ``0.0``;
 - The color's red component, ranging from 0.0 to 1.0.

`float <https://cppreference.com/c/language/type>`_ **g** = ``0.0``;
 - The color's green component, ranging from 0.0 to 1.0.

`float <https://cppreference.com/c/language/type>`_ **b** = ``0.0``;
 - The color's blue component, ranging from 0.0 to 1.0.

`float <https://cppreference.com/c/language/type>`_ **a** = ``1.0``;
 - The color's alpha component, ranging from 0.0 to 1.0. A value of 0.0 means a fully transparent color. A value of 1.0 means a fully opaque color.

.. note::

    Some game-defined colors might ignore alpha completely.

.. note::

    Not yet implemented.

`struct <https://en.cppreference.com/c/language/struct>`_ **PC_ColorHSV**
_________________________________________________________________________
A struct representing a color in HSV format.

`float <https://cppreference.com/c/language/type>`_ **h** = ``0.0``;
 - The color's hue component, ranging from 0.0 to 1.0.

`float <https://cppreference.com/c/language/type>`_ **s** = ``0.0``;
 - The color's saturation component, ranging from 0.0 to 1.0.

`float <https://cppreference.com/c/language/type>`_ **v** = ``0.0``;
 - The color's value (brightness) component, ranging from 0.0 to 1.0.

`float <https://cppreference.com/c/language/type>`_ **a** = ``1.0``;
 - The color's alpha component, ranging from 0.0 to 1.0. A value of 0.0 means a fully transparent color. A value of 1.0 means a fully opaque color.

.. note::

    Some game-defined colors might ignore alpha completely.

.. note::

    Not yet implemented.

Constants
---------
**WHITE** = ``(PC_Color8){255,255,255,255};``

**RED** = ``(PC_Color8){255,0,0,255};``

**GREEN** = ``(PC_Color8){0,255,0,255};``

**BLUE** = ``(PC_Color8){0,0,255,255};``

**CYAN** = ``(PC_Color8){0,255,255,255};``

**MAGENTA** = ``(PC_Color8){255,0,255,255};``

**YELLOW** = ``(PC_Color8){255,255,0,255};``

**BLACK** = ``(PC_Color8){0,0,0,255};``

Enums
-----
