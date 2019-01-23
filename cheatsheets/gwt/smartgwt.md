# SmartGWT
is a widget lib for GWT
1. based on GWT = Google Web Toolkit, in Java, for AJAX, compiles to HTML&JS&CSS
2. http://code.google.com/p/smartgwt/ showcases:
    1. https://www.smartclient.com/smartgwtee/showcase/
    2. https://www.smartclient.com/smartclient/showcase/
3. has offline-storage functions
4. SmartGWT starts supporting Selenium from version 2.2. and provides some user extensions for Selenium
5. Don’t mix classic GWT with SmartGWT. It’s just not really compatible
## Setup
### Dependencies:
1. smartgwt.jar
2. smartgwt.skins.jar
### Configuration/Styling options
1. WEB-INF/web.xml  # filters, servlets, welcome-file...
2. myapp.css
2. myapp.html
    1. eg. you can set &lt;script&gt;var isomporphicDir = "myapp/sc/";&lt;/script&gt;
    2. references CSS & compiled JS (from your java code)
### myapp.gwt.xml = GWT Config
```xml
<module rename-to='myapp'>
    <entry-point ... />
    <source path... />
    ...
    <inherits name="com.smartgwt.SmartGwt" />
```
### myapp.java
```java
public class MyApp implements EntryPoint {
    private DynamicForm mainForm; //com.smartgwt.client.widgets.form.DynamicForm
    private TextItem textItem;
    private IButton button;
    public void onModuleLoad() {
        mainForm = new DynamicForm();
        textItem = new Textitem("Name");
        button = new IButton("Click");
        button.addClickHandler(new ClickHandler() {
            @Override
            public void onClick(ClickEvent e) {
                SC.say("Hi "+textItem.getValue());
            }
        });
        mainForm.setFields(textItem/*,textItem2,textItem3*/);
        RootPanel.get().add(mainForm);
        RootPanel.get().add(button);
    }
}
```
# SmartClient
ha smartClientSDK
# GWT
