# An homemade proofing box

Please visit my blog to complete build istructions: [detailed instructions](http://matteolel.ddns.net/posts/homemade-proofing-box/)

## Components

-   Arduino Nano or similar (I used a AZDelivery Nano based on ATmega328P Micro Controller)
-   LM35 (temperature sensor)
-   IRF540N (Mosfet NPN)
-   1K Ohm resistor
-   An heat cable (33Ω/meter)
-   a 20V power supply (for the heat cable)
-   a 5V power supply (for arduino)

## Schematics

[![img](/images/schematics.jpg)](file:///images/schematics.jpg)

## Some tests

I made some tests with the Serial Plotter from Arduino IDE.

Here setting 24°C as target temperature:

[![img](/images/test-24.png)](file:///images/test-24.png)

Here setting 30°C as target temperature:

[![img](/images/test-30.png)](file:///images/test-30.png)

In the last one, after some minutes, I switched off the heating source's power supply (at the end you can see the curve goes down).

## License

See the [LICENSE](LICENSE.md) file for license rights and limitations (GNU LGPLv3).
