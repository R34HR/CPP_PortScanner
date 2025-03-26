<h1>The PrtScanner Tool:</h1>
<p>The PrtScanner tool is a Port scanning tool that scans any valid Ipv4 Address or URL  writtin in C++ using the SFML (Simple and Fast Multimedia Library) library. </p>

<h2>State Of Development:</h2>
<p>Currently released version 1.0. Development is focused on fixing Socket Status conditions when scanning an address.</p>

<h2>How to Utilize the tool: </h2>
<h3>Step 1: Clone the repo to your desired location.</h3>
<h3>Step 2: Ensure to download the SFML library to your computer from <a href='https://www.sfml-dev.org/download/'> here</a>.</h3>
<h3>Step 3: To Compile the program:</h3>
<h4>(Ensure to be on the folder where you cloned the repo)</h4>
<h4>&emsp; Linux:</h4>
<p>On the terminal: </p>
<p>&emsp; 1st, run --> 'g++ -c main.cpp' , which will produce a 'main.o' file needed to compile the tool.</p>
<p>&emsp; 2nd, run --> 'g++ main.o -o sfml-app -lsfml-network -lsfml-system', this command will produce 'sfml-app' file which will be the executable for the tool.</p>
<p>&emsp; Lastly, run --> './sfml-app', which will run the tool on the command line. </p>
