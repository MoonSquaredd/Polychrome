Colorset Api
============

An Api for getting and setting game-defined colors.

Functions
---------

`PC_Color8 <api_polychrome.html#struct-pc-color8>`_ **GetARGBColorById**\(`int32_t <https://en.cppreference.com/c/types/integer>`_ colorId\)
_____________________________________________________________________________________________________________________________
 Returns a color from the ARGB game-defined colors list by id. Check the enum `ARGBColorId <api_polychrome.html#enums>`__ for the list of valid ids.

.. code-block:: c

	static const Polychrome_Api* _polychromeApi;

	// [...]

	// Get the counter hit flash color.
	PC_Color8 counterHit = _polychromeApi->Colorset->GetARGBColorById(PC_COLOR_COUNTER_HIT_FLASH);

.. caution::

	This method is faster than GetARGBColorByName but more fragile to updates.

`PC_Color8 <api_polychrome.html#struct-pc-color8>`_ **GetARGBColorByName**\(`char* <https://en.cppreference.com/c/language/type>`_ colorName\)
_____________________________________________________________________________________________________________________________
 Returns a color from the ARGB game-defined colors list by name. Valid names are the same listed in colors.txt.

.. code-block:: c

	static const Polychrome_Api* _polychromeApi;

	// [...]

	// Get the counter hit flash color.
	PC_Color8 counterHit = _polychromeApi->Colorset->GetARGBColorByName("CounterHitFlash");

.. caution::

	This method can be slower than GetARGBColorById but less fragile to updates.




