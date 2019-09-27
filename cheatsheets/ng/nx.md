<link rel="stylesheet" href="../_github-markdown.css">

# Monorepo approach with Nx from Nrwl
## CLI
```sh
npm install -g @angular/cli @nrwl/schematics     # install nx
# create wp - alternative 1:
npx create-nx-workspace mywp                     # generates your workpspace
# create wp - alternative 2:
ng new mywp --collection=@nrwl/schematics
# create wp - alternative 3: use the Angular Console (=Web App)

ng g app myapp                                   # generates an ng app
# generates an ng app in apps/mys/myapp with tags: (libs can be tagged too!)
ng g app myapp --directory=mys --routing --tags=scope:shared,type=desktop

ng generate lib mylib --ngmodule                 # generate a lib
ng serve myapp                                   # run the just generated Ng App
# generate a backend (nestjs-based (similar to Ng, just for node, TypeScript with @Injectable's))
# http://localhost:3333/api returns JSON
ng g node-app mybackend --frontendProjects=myapp
ng serve mybackend

# build: (here: build only from change affected apps)(master=git branch)
npm run affected:build -- --base=master --parallel --maxParallel=4
```
The Nx CLI is built on top of the Ng CLI

### "npx create-nx-workspace mywp" generates folders & files:
1. /apps/
    1. subdirs(or its subdirs) contain your apps (Ng, React(ng add @nrwl/react), Express or NestJs(ng add @nrwl/nest), etc.)
1. /libs/
    1. be be feature-, ui-, data-access-, utility- libraries
    1. use index.ts in the root of each lib to define public API
1. /tools/schematics/
    1. for your specific ng schematics
1. angular.json, nx.json, package.json, tsconfig.json, etc.
    1. **angular.json** lists your projects
    1. **package.json** with a lot of predefined scripts (build, test, start, update, schematics, format:check, dep-graph ...)
    1. **nx.json** (contains also tags, dependencies)

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
        <br> (or)<br>
    > ng add @nrwl/schematics
1. Nx hasa NgRx extension: import { DataPersistence } from '@nrwl/nx';
    1. for handling optimisticUpdate or pessimisticUpdate
    1. for fetching with dataPersistence.fetch(...)
    1. Data Fetching On Router Navigation: dataPersistence.navigation(...)
