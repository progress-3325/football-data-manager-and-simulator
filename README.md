This project is under the MIT license.
You are free to use this code as a template to your own project or for what it's actually programmed for.
Made in Visual Studio Community 2022.
When downloading the project, move the folder in C:\Users\Administrator\source\repos (if your visual studio directory is the default one, if not move it into your set directory, if your account isnt named Administrator change it to your own).
c++ version C++17 (default in visual studio is C++17).
Used MSVC.
You will have to go in your solution explorer, right click the project, then press properties < C++ < Language < option C++ Language Standard < select ISO C++17 (or a newer version) < click apply at the bottom right corner of the properties window.
To be able to include nlohmann/json (this is the github page) you will need to open properties again < C++ < General < option Additional Include Directories < paste C:\Users\Administrator\source\repos\football data manager\include (if your pc user isnt Administrator change it to your own, and if you set up a custom directory for Visual Studio projects then move it there).
I thank nlohmann (Niels Lohmann) for creating the json library, it would've been a real headache if I had to figure out a way to save data on my own, I plan on doing it in the future as a project though, I aspire to know more and more.

I plan on adding linux support in the future
