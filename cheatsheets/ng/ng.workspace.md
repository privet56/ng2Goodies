# Angular Workspace

## Pre-Requisites
* Source code should **not** refer to project-absolute paths (reference always **relative**!)
    <br>Wrong:
    ```ts
    import {MyService} from "app/service/my.service";
    {path: 'path', loadChildren: () => import('app/modules/admin/my.module').then(m => m.MyModule)},
    ```
* you will have to adjust references pointing into /node_modules/ of the angular workspace in your SCSS files

(both of these issues will cause build errors)

## Workspace-aware files
* angular.json has to be changed: use the correct paths to the apps and libs in /projects/*

### Gotchas
* when moving directories within IntelliJ, some references are changed wrongly (suffix .ts is changed to .js)
* when moving directories within IntelliJ, references starting with './ are changed without effect (./ is removed)

## Structure
* **/projects/** contains the angular apps and libs
* **/node_modules/** is for all projects (installed with 'npm ci')
* **angular.json** specifies the settings for the projects (with paths relative from angular.json)
* **pom.xml** builds the default app (as set in angular.json "defaultProject") into target/classes *without any changes*
* **tsconfig.json** & **tslint.json** contain general settings
    * project-specific tsconfig.*.json & tslint.json extend/override these files

<hr>

# git subtree
Use remote ng libs in your projects by checking them out inside /projects/

```ts
# ensure you have no uncommitted changes
cd %YOUR-GIT-PROJECT-ROOT%
# the following command results in commits!
git subtree add  --prefix projects/nglib git@mysrvgitlab.my.de:ng/nglib.git develop --squash
# update from remote
git subtree pull --prefix projects/nglib git@mysrvgitlab.my.de:ng/nglib.git develop --squash
### you can change & commit & push inside of your subtree, too!
```

#### 'git subtree' Parameters
* The **--prefix** parameter defines the root directory for the cloned repository
    * Example: projects/nglib
* then add the remote git repo
    * Example: git@mysrvgitlab.my.de:java/nglib.git
* then add the branch name
    * Example: develop
* **--squash** the entire commit history
    (so that the history of the subtree-repo is **not** included into the main project history)

#### 'git subtree' Gotchas
* Error message: "Working tree has modifications. Cannot add."
    * call "git reset --hard" (all your local changes will be lost!)
