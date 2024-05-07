# Stager (STAGeR)
Stager is a runtime environment for ACT (adventure/choice tree) files, which are high-level files that contain choose-your-own-adventure stories.
## Creating an act
Steps:  
1. Make a text file
2. Write an act (using ACT syntax)
3. Rename the file to have a `.act` file extension

If you want to edit an ACT file, but double-clicking it triggers an app to open (like Stager or Photoshop), simply right-click on it > Edit with Notepad (or another text editor of your choice)

*Note: I personally recommend Visual Studio Code to edit ACT files.*
## Running an act
Running an act file is easy. Either load Stager and type in the name of the act you would like to run *(do not include .act)*, or just open an act with Stager (you can also drag and drop acts onto stager.exe).

*IMPORTANT: you can only load an act by name if it is in the given "input" folder.*
## Interacting
Once an act has begun, you simply type the number that corresponds with the choice given.
# ACT Syntax
## Descriptors
Acts should begin with a title, the author(s) and a description. These are called the *descriptors* and are declared like this:
```
T: title\
A: author(s)\
D: description\
```
Replace `title`, `author(s)`, and `description` with the name of your story, your name, and a brief description (respectively).
As you can see, backslashes are used as delimiters. This is important, as this is consistent throughout the whole file. 

*Note: In the case that there are multiple authors, put them within the same "`A:   \`" section. If you instead make two separate author lines, only the first one will be used.*

## Elements
After that, we have the interactive story pieces, called *elements*. The syntax is formatted like this:
```
name: content{
	choice\destination\
	choice\destination\
	choice\destination\
}
```
Replace `name` with the name you want to refer to it as.

*IMPORTANT: Stager starts at the element with the name "start". If there is no start element, it will fail to run.*  

Replace `content` with bits of the story. Also add a question, unless it is the end of the story.

Inside curly brackets, put as many choice and destination pairs as you want:  
Replace `choice` with a decision the player can choose to make.  
Replace `destination` with the name of the element you should be taken to if you choose the preceding decision.

You can end the story by leading to an element without any choices (empty brackets).

Example act:
```  
T: Example\
A: Rtificr\
D: An example act\

start: Where do you want to go? {
	The store\store\
	Home\home\
	The park\park\
}
store: You went to the store! {}
home: You went home! {}
park: You went to the park! {}
```

If you were to choose to go to the store, it would take you to the element named "`store`". 

## Formatting Advice
*In ACT files...*
* Newlines do absolutely nothing.
* Backslashes can *not* be used as escape characters.
* Whitespace surrounding semantic colons is ignored.

### Name formatting
Adding whitespace at the start of an element name or destination may give unintended behavior.

*Note: some examples of "leading spaces" may not show up on the GitHub mobile app.*

The name of the element ` start:Hello! {}` is ` start`, not `start` (note the leading space).  
The destination of the choice `Go to work\ work` is ` work` not `work` (note the leading space).

This may trip you up if you fail to eliminate whitespace and wonder why "Choice #1 leads to nothing".

### Descriptor formatting
The descriptors also experience the same formatting issues that choices may have.
However, there are some other things to worry about.

If you happen to name an element "T", "A", or "D", you should be fine as long as you already have all your descriptors at the top of the file.  

If any element named "T", "A", or "D" happens to come before the respective TAD descriptor, or if the descriptor doesn't exist, it will be used in place of the real descriptor.
This may look weird but is otherwise harmless.
## Visual guide
![act-format-2](https://github.com/rtificr/stager/assets/102625530/18ea79a4-dc33-41a2-a208-82afbcf73e20)
## Cheatsheet
|**Keyword**|**Usage**|
|-----------|---------|
|T:|Declares the following text (until a backslash) as the title of the story|
|A:|Declares the following text (until a backslash) as the author(s) of the story|
|D:|Declares the following text (until a backslash) as the description of the story|
|start|When used as the title of an element, the element will be used as the entry point of the file|
|&#92;|Used as a delimiter in act files (and *not* as an escape character)|
|{ }|Marks the text between them to be interpreted as choices|
