# The-safe-project
🔒 Embedded System Safe Project - Password Protected Safe 🔒
the safe project! 🚀 Developed a password-protected safe using an Atmega32 microcontroller with a robust software architecture.

Hardware Components:
Atmega32
Internal EEPROM.
LCD Display.
Keypad.
Button.

Software Architecture:
- MCAL Layer
- HAL Layer (LCD, Keypad, EEPROM, Button Drivers)
- Application Layer: Orchestrating the overarching application logic.

💡 Key Features:

Secure Password Setup: Users can set a 4-digit password securely.
Reset Option: Includes a reset button for password recovery.
Attempts Limit: Limited attempts for password entry to enhance security.
LCD Feedback: Informative messages displayed on an LCD for user guidance.
🛠️ How it Works:

Initial setup prompts users to set a new password.
The reset button allows users to recover their password.
After a set number of incorrect attempts, users need to wait 30s before trying again.
![Screenshot_1](https://github.com/MariamAshraff/The-safe-project/assets/118696706/cea098eb-747e-4a19-a041-81035152726b)
