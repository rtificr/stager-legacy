# Stager (STAGeR)
Stager is a runtime environment for ACT (adventure/choice tree) files, which are high-level files that contain choose-your-own-adventure stories.
## Running an act
Running an act file is easy. Either load Stager and type in the name of the act you would like to run *(do not include .act)*, or just open an act with Stager (you can also drag and drop acts onto stager.exe).

*Important: you can only load an act by name if it is in the given "input" folder.*
## Interacting
Once an act has began, you simply type the number that corresponds with the choice given.
# ACT Syntax
## Descriptors
Acts should begin with a title, the author(s) and a description. These are called the *descriptors* and are declared like this:
```
T:TITLE HERE\
A:AUTHOR(S) HERE\
D:DESCRIPTION HERE\
```
As you can see, backslashes are used as delimiters. This is important, as this is consistent throughout the whole file. 

*Note: In the case that there are multiple authors, put them within the same "`A:   \`" section. If you instead make two separate author lines, only the first one will be counted.*

## Elements
After that, we have the interactive story pieces, called *elements*. The syntax is formatted like this:
```
NAME:CONTENT{
CHOICE\DESTINATION\
CHOICE\DESTINATION\
CHOICE\DESTINATION\
}
```
The `NAME` can be thought of as the index of the element. 

*Important: Stager starts at the element with the name "start". If there is no start element, it will fail to run.*
The `CONTENT` is usually the question of the element, but not always. 

Inside some curly brackets, you have the `CHOICE` and the `DESTINATION`. The choice is a decision the player can choose to make. After a backslash, the destination is the name of the element that choice should take you to if you choose it, and then add another backslash on the end.

Example act:
```
T:Example\
A:Rtificr\
D:An example act\

start:Where do you want to go? {
The store\store\
Home\home\
The park\park\
}
store:You went to the store! {}
home:You went home! {}
park:You went to the park! {}
```

If you were to choose to go to the store, it would take you to the element named "`store`". 
You might notice that `store`, `home`, and `park` do not have any choices. This signifies that you have reached the end.

## Formatting Advice
### Choice formatting
Adding whitespace of any kind at the start of a choice or question is not recommended. It will show up when running.

`start: Hello! {}` will output as " Hello!"

### Name formatting
Adding whitespace at the start of an element name or destination may give unintended behavior.

The name of the element `  start:Hello! {}` is " start", not "start" (note the leading space).  
The destination of the choice `Go to work\ work` is " work" not "work" (note the leading space).

This may trip you up if you fail to eliminate whitespace and wonder why "#1 leads to nothing".

### Descriptor formatting
The descriptors (TAD) also experience the same formatting issues that choices may have.
However, there are some other things to worry about.

If you happen to name an element "T", "A", or "D", you should be fine as long as you already have all your descriptors at the top of the file.  
If any element named "T", "A", or "D" happens to come before the respective TAD descriptor, or if the descriptor doesn't exist, it will be used in place of the real descriptor.
This may look weird but is otherwise harmless.

## Visual guide
![act-format](https://github.com/rtificr/stager/assets/102625530/1ec6f5a4-c011-48a5-a5c3-4f79c31dcfce)
