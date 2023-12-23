
1. Clone crow repository:
  ```bash
  git clone https://github.com/ipkn/crow.git
  ```
  
2. Copy crow include folder into your include project
   
3. Install crow dependency
  ```bash
  brew install boost
  ```

4. build
   ```bash
   chmod +x build.sh
   ```

5. vscode settings.
  .vscode folder, c_cpp_properties.json:
  ```json
  {
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/local/include", // Add this line to include Boost
                "/usr/local/Cellar/boost/1.83.0"// Add any other necessary paths
            ],
            "macFrameworkPath": [
                "/System/Library/Frameworks",
                "/Library/Frameworks"
            ],
            "compilerPath": "/usr/bin/clang",
            "cStandard": "c11",
            "cppStandard": "c++17"
        }
    ],
    "version": 4
  }
  ```
