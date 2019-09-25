<link rel="stylesheet" href="../_github-markdown.css">

# Monorepo approach with Nx from Nrwl
## CLI
```sh
#pre-requisite: Nx installed
npx create-nx-workspace mywp                     # generates your workpspace
#alternative:
ng new mywp --collection=@nrwl/schematics
ng g app myapp                                   # generates an ng app
ng generate lib mylib --ngmodule                 # generate a lib
ng serve myapp                                   # run the just generated Ng App
# generate a backend (nestjs-based (similar to Ng, just for node, TypeScript with @Injectable's))
# http://localhost:3333/api returns JSON
ng g node-app mybackend --frontendProjects=myapp
ng serve mybackend
```
The Nx CLI is built on top of the Ng CLI

### "npx create-nx-workspace mywp" generates folders & files:
1. /apps/
    1. subdirs contain your apps (Ng, React or NestJs, etc.)
1. /libs/
1. /tools/schematics/
    1. for your specific ng schematics
1. angular.json, nx.json, package.json, tsconfig.json, etc.
    1. **angular.json** lists your projects
    1. **package.json** with a lot of predefined scripts (build, test, start, update, schematics, dep-graph ...)

## Advantages
1. You can **share** models/interfaces between Ng frontend and NestJs backend.
1. You can easily use **libs**
1. Nx helps use **NgRx** by providing a convention / best practices
    ```sh
    ng generate ngrx app --onlyEmptyRoot --module=apps/myapp/src/app/app.module.ts
    ng generate lib mylib --ngmodule
    ng generate ngrx --module=libs/mylib/src/mylib.module.ts
    ```
    Generates effects, reducers, e2e(-marble-)tests, etc.
1. Support for old angularjs:
    ```sh
    ng generate app admin
    ng generate upgrade-shell supportLegacy --name=support-legacy --module=apps/admin/src/app/app.module.ts
    ```
1. has advanced linters (ng lint)
1. can convert normal Ng app into an Nx Workspace:
    > ng generate workspace mycurrentapp --collection=@nrwl/schematics
