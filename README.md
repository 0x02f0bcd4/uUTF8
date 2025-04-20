# uUTF8

A small UTF8 library written in C. Pronounced mu-UTF8 (The Greek alphabet Mu).

## Intention

I was looking for an UTF8 library like the Lua Programming Language has for C, but I found none. There are some compiler specific library (like GCC's one) but I couldn't find a properly portable UTF8 library. Also I have never done anything like string manipulation outside of what I learnt in DSA books, and I didn't have anything to do on hand. So, I took a swing.

## Usage 

Refer to the documentation.

## License and others

This full project is licensed under GNU GPL License Version 3. Refer to the LICENSE.TXT for more information.

## Releases

You can find it in the the release tags section in the github project page. Linux and other platforms' releases aren't available. You can build it yourself. Refer to documentation to know how to build(and additionally test) the project.

## Issues

I don't use GitHub to track them. Refer to my website for that.

## Improvement and additions

You can send pull request. Upon revising the pull request, I may merge.

### Casing style

I use a pretty much universal casing style for almost all of my programming language choices (except where the style implies something, like in the case of Golang). These are - 
 - camelCase for function name.
 - g_VarName for global variable name.
 - ClassOrStructName for struct or class name.
 - local_var for variable name.
 - IInterfaceName for interface name (I-prefixed)

### Coding style

Like in the case of Casing Style, I also use pretty much an universal coding style for almost all of my programming language choices (except where the style implies something, like in the case of Python). These are -

 - Instead of using a single alphabet var name, use long name(even at the cost of taking longer to write). However, an exception to this case is loop variable name. But even then, try to be as much specific as you can when nested loop is in action.
 - Use tabs. Overly long lines are allowed. I prefer using tabs (\t, with 4 spaces) and line wrap.
 - Don't give me clean code bullshit.
 - Prefer composition over inheritance (if supported).

## Versioning

This project uses [semver](https://semver.org/). Initial stable release is 0.0.0.

