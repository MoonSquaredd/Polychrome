Colorset Api
============

An Api for getting and setting game-defined colors.

Functions
---------

`PC_Color8 <api_polychrome>`_ **GetARGBColorById**\(`int32_t <https://en.cppreference.com/c/types/integer>`_ colorId\)
_____________________________________________________________________________________________________________________________
 Returns a color from the ARGB game-defined colors list by id. Check the enum `ARGBColorId <api_polychrome>`__ for the list of valid ids.

.. code:: c
    :number-lines:

    static const Polychrome_Api* _polychromeApi;

    // [...]

    // Get the counter hit flash color.
    PC_Color8 counterHit = _polychromeApi->Colorset->GetARGBColorById(PC_COLOR_COUNTER_HIT_FLASH);
