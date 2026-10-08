<div align="center">
  
<h1>RaceDash</h1>
<h4>C++ and SFML application for visualizing and analyzing vehicle telemetry data that allows you to load your own CSV files</h4>


<h6>Some photos of the program</h6>
<img width="550" height="400" alt="image" src="https://github.com/user-attachments/assets/70a30bef-d09c-482b-b9a7-c7cb34834e2e" />
<hr>
<img width="550" height="400" alt="image" src="https://github.com/user-attachments/assets/bc8f6723-3d90-4549-9d55-84a690256476" />
<hr>
<img width="550" height="400" alt="image" src="https://github.com/user-attachments/assets/49a73eac-a543-447a-864d-602e3514c5db" />

</div>
<ul>
<li>Language: C++17</li>
<li>Graphics: SFML-3.0.2</li>
<li>Features: Custom CSV loader, playback speed control (arrow keys), dynamic warning alerts</li>
<li>2 dashboard layouts: analog & race digital</li>
</ul>
<hr>
<h3>HOW TO RUN</h3>
<h4>1. Clone the repository:</h4>
  <h6><code>git clone https://github.com/Rosepose95/RaceDash.git</code></h6>
   
<h4>2. Open RaceDash.sln in Visual Studio </h4>

<h4>3. Right-click on the project in the Solution Explorer and select Properties (Configuration = DEBUG, Platform = X64, C++ standard c++17)</h4>
  <h6> Include path: Go to C/C++ → General → Additional Include Directories and change the path to your SFML include folder (C:\SFML-3.0.2\include)</h6>
  <h6> Library path: Go to Linker → General → Additional Library Directories and change the path to your SFML lib folder (C:\SFML-3.0.2\lib)</h6>
  <h6>Copy content from SFML bin directory (C:\SFML-3.0.2\bin) then paste it to your directory with project files</h6>
  <h6> Dependencies: Go to Linker → Input → Additional Dependencies and paste:</h6>
  <h4>FOR DEBUG</h4>
  <h6>sfml-graphics-d.lib
      sfml-window-d.lib
      sfml-system-d.lib</h6>
  <h4>FOR RELEASE</h4>
  <h6>sfml-graphics.lib
    sfml-window.lib
    sfml-system.lib</h6>
    
<h4>4. Now you can prepare your own CSV file which must look like this:</h4>
<img width="300" height="400" alt="image" src="https://github.com/user-attachments/assets/aa39329e-2c66-4f3e-8251-16b6430e9eb4" />

<h4>5. Now you can run the project and analyze your own file!</h4>
<hr>
