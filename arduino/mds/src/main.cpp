/* EG-110
 * SNHU, CETA
 *
 * The main component of our source code.
 */

#include "Arduino.h"

// Settings/config
#include "pindefs.h"

// Libs
#include "HUSKYLENS.h"
#include "SoftwareSerial.h"
#include "drivetrain.h"

// Objects/Components
const Drivetrain drivetrain = Drivetrain(STAR_MOTOR, PORT_MOTOR);
const HUSKYLENS huskylens;

SoftwareSerial huskySerial(HUSKY_RX, HUSKY_TX);

// Delete me
float superI = 0;

void printError(String _error)
{
    Serial.print("\x1B[31mi^2c Error: ");
    Serial.println(_error);
    Serial.print("\x1B[0m");
}

void printResult(HUSKYLENSResult result); // Move me

void setup()
{
    // Setup Serial
    Serial.begin(DEV_SERIAL_SPEED);
    huskySerial.begin(HUSKY_SERIAL_SEED);

    // Print MOTD
    Serial.println(MOTD);

    // // Setup huskylens (bleh)
    // while (!huskylens.begin(huskySerial))
    // {
    //     printError("Error starting huskylens, halting until complete.");
    //     delay(RETRY_PAUSE);
    // }
}

void loop()
{
    superI = superI + 0.01;

    drivetrain.setChassisVector(int(sin(superI) * 255), 0);

    delay(25); // Never do this!

    // if (!huskylens.request())
    //     Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    // else if (!huskylens.isLearned())
    //     Serial.println(F("Nothing learned, press learn button on HUSKYLENS to learn one!"));
    // else if (!huskylens.available())
    //     Serial.println(F("No block or arrow appears on the screen!"));
    // else
    // {
    //     Serial.println(F("###########"));
    //     while (huskylens.available())
    //     {
    //         HUSKYLENSResult result = huskylens.read();
    //         printResult(result);
    //     }
    // }
}

void printResult(HUSKYLENSResult result)
{
    if (result.command == COMMAND_RETURN_BLOCK)
    {
        Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW)
    {
        Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
    }
    else
    {
        Serial.println("Object unknown!");
    }
}
