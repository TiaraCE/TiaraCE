**Widget types**

*game model (not  implemented)*
Used in the Main menu widget tag. To me, it behaves like a typical container widget but used in the main menu widget which happens to be the starting widget tag in
an UI map. Since we are not sure of its significance, we can assume it like a container tag for our implementation.

*container*
Can contain other various types widgets as children.
Used in various screens other than the main menu. Usually as a mother of all widgets in a particular screen. Responds to fade flag and fade timer. During fading, all
child widgets are faded equally in the same time and same manner.

*text box*
Usually doesn't contain other any children but has provisions for that in HEK. Used as an item in a list (with events) or a widget to show a piece of graphics or text
on screen. Supports bitmap sequences for animations or for use as buttons. When used as buttons bitmap data group 0 is used as default graphics, while data
group 1 is used as hover graphics. The bitmap switches between data groups on mouse hover.

*spinner list*
Shows children one at a time. Typically used with dpad movement flag for navigating. Also spinners used in the UI maps rotate through an array of strings
from a string list. For example, the Mouse sensitivity widget in UI.map.

*column list*
Usually contains several text widgets as list items, used with 'dpad movement thru list items' flag for navigating. Also pass unhandled events flag is used to make the
events of  children text box widgets work.

*description widget*
Its not really an widget type but any container can be a conditional widget of another column or spinner list. In that case, this widget is shown as a typical container
behind the actual widget to which it belongs to. Any widget which is a child to a description widget will switch bitmaps (across several data blocks) and strings in the
string list, as and when a particular list item or child of column or spinner list is focused. The order of bitmap data blocks and string are the same as the order of
list items in the column list or spinner list widget. It is not usually a children of another widget conventionally not mandatory.

*conditional widget*
Any type of widget can be a conditional widget to another widget. Its usually launched of an event in the calling widget fails. For example the user creation screen
is a conditional widget to the campaign menu item in the main menu. The function it has is new campaign if no profile  found. If no profile is found then the event
generates a failure and the conditional widget is called instead.

**Specifications**
*Player index*
Determines the player who will control a particular widget and whose events would be registered. Used for multiplayer
or split screen scenarios. 'Any Player' means all players can access that widget equally.

*Controller index*
Same as Player Index used for child widgets specification.

*Background Image*
Bitmap that is shown in the background of that widget.
SPECIAL BEHAVIOR ON USE OF OPEN SAUCE.
If background bitmap bounds are set to [0, 0, 480, 640] then bitmap stretches fullscreen. Any other value would stop that behavior, also set image location in the 4:3 frame (this conceptual frame is center aligned). Bottom and right bounds set the height and width of the image. If bounds top and left are set to negative then the image will try to fit in bottom and right bounds. In a value near about -1000 to -10000 of t and l, a large high resolution bitmap will fit completely in the bounds. A trick used in SPV3 UI for putting in high res graphics.

*Fade timer*
Fades all child widgets including itself after said amount of time in seconds. Fading will cause the widget to disappear or unload or get destroyed. Any event associated with 'on widget destroyed' would be activated.

*Fade duration*
Time it takes to fade the widgets from full opacity to fully transparent.

*String List*
Show text from a string list in bounds set in the string list attributes.

*String List index*
Index of the string in the string list to show.

*Event Handlers*
Sets functions to run, scripts to run, and/or widgets to load when a particular event occurs. Also used for handling inputs in some cases.
