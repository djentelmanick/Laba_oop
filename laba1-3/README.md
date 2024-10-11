## Инструкция для корректной работы в VSCode

Для *main.cpp* и *builder.cpp* выберите кодировку **"Cyrillic Windows 1251"**

Перейдем в папку laba1
```
cd C:\path_to_laba1\laba1
```

Для создания консольного приложения
```base
g++ main.cpp builder.cpp -o my_program -mconsole
```

Для запуска приложения
```base
.\my_program.exe
```