# Single-header C++ library for parameter file

## Usage

Pass the file name to the constructor.

```cpp
param::parameter param(filename);
```

You can check the error on reading file as

```cpp
  if (!param) {
    std::cerr << "Error occurs" << std::endl;
  }
```

The format of an input file (a parameter file) is `key=value`.

```sh
# Comment
bool=yes
int=12345
double=12.345
```

Lines starting with `#` are considered comments.

You can obtain the values by the keys.

```cpp
bool b = param.get<bool>("bool");
int  i = param.get<int>("int");
double d = param.get<double>("double");
```

You can specify the default value at the second argument if a key does not exist.

```cpp
bool b = param.get<bool>("non-existing key", false);
int  i = param.get<int>("non-existing key", 0);
double d = param.get<double>("non-existing key", 0.0);
```

## License

This software is released under the MIT License, see [LICENSE](LICENSE).
