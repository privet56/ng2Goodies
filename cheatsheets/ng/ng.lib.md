<link rel="stylesheet" href="../_github-markdown.css">

# Angular Library

## Create Workspace, Lib and App:
```sh
# generate an empty workspace without project
ng new myworkspace --createApplication=false
cd myworkspace
# generates an ng lib in the subdir /projects/
ng generate library mylib
# generate an app
ng generate application myapp
```
## Structure after generating the above projects:

1. **myworkspace/angular.json**
    1. references now 2 projects:
        1. projects/mylib: projectType: "library"
        1. projects/myapp: projectType: "application"
    1. has now a dependency to **ng-packagr**
    1. **tsconfig.json** has now a reference to "paths"."mylib" dist folder<br>(so myapp can reference mylib from dist)
1. the generated lib mylib has **/projects/mylib/src/lib/\*** containing the sources of the lib, inclusive an ngModule
1. the generated **/projects/mylib/src/public_api.ts** defines the public API of mylib

## Usage

1. add a command into myworkspace/package.json to build your lib<br>
(can be started with 'npm run mylibbuild')<br>
(generates the angular lib Package into /dist/):
    ```ts
        scripts: {
            ...
            "mylibbuild": "ng build mylib",
    ```

1. in your app AppModule, you can import the public API of mylib
    ```ts
    import {MyLibModule} from 'mylib';
    ...
    imports [
        ...
        MyLibModule
    ]
    ```
    ...so, you can now use the lib components/services in your app components!

## Package the Lib
```sh
cd mylib/dist/mylib/
# generate a tarball (mylib-0.0.1.tgz)
npm pack
# this command adds a new entry in package.json:dependencies:
    # "mylib": "file:dist/mylib/mylib-0.0.1.tgz"
    # tsconfig.json "paths"."mylib is not needed anymore...
npm install ./dist/mylib/mylib-0.0.1.tgz
```
#### Publish the Lib
```sh
cd dist/mylib
# Verdaccio is an open source npm repo for your private libs...
npm publish --registy http://verdaccio:4873
#after publishing it, you can install (instead of a .tgz archive)
npm i mylib --registy http://verdaccio:4873 --save
```
1.  instead of specifying --registry, you can also create a **.npmrc** file in your project root and insert the line:<br>
registry=http://verdaccio:4873
