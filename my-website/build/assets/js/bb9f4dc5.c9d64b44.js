"use strict";(self.webpackChunkmy_website=self.webpackChunkmy_website||[]).push([[643],{3905:(e,t,r)=>{r.d(t,{Zo:()=>u,kt:()=>m});var a=r(7294);function n(e,t,r){return t in e?Object.defineProperty(e,t,{value:r,enumerable:!0,configurable:!0,writable:!0}):e[t]=r,e}function o(e,t){var r=Object.keys(e);if(Object.getOwnPropertySymbols){var a=Object.getOwnPropertySymbols(e);t&&(a=a.filter((function(t){return Object.getOwnPropertyDescriptor(e,t).enumerable}))),r.push.apply(r,a)}return r}function l(e){for(var t=1;t<arguments.length;t++){var r=null!=arguments[t]?arguments[t]:{};t%2?o(Object(r),!0).forEach((function(t){n(e,t,r[t])})):Object.getOwnPropertyDescriptors?Object.defineProperties(e,Object.getOwnPropertyDescriptors(r)):o(Object(r)).forEach((function(t){Object.defineProperty(e,t,Object.getOwnPropertyDescriptor(r,t))}))}return e}function i(e,t){if(null==e)return{};var r,a,n=function(e,t){if(null==e)return{};var r,a,n={},o=Object.keys(e);for(a=0;a<o.length;a++)r=o[a],t.indexOf(r)>=0||(n[r]=e[r]);return n}(e,t);if(Object.getOwnPropertySymbols){var o=Object.getOwnPropertySymbols(e);for(a=0;a<o.length;a++)r=o[a],t.indexOf(r)>=0||Object.prototype.propertyIsEnumerable.call(e,r)&&(n[r]=e[r])}return n}var s=a.createContext({}),p=function(e){var t=a.useContext(s),r=t;return e&&(r="function"==typeof e?e(t):l(l({},t),e)),r},u=function(e){var t=p(e.components);return a.createElement(s.Provider,{value:t},e.children)},c={inlineCode:"code",wrapper:function(e){var t=e.children;return a.createElement(a.Fragment,{},t)}},d=a.forwardRef((function(e,t){var r=e.components,n=e.mdxType,o=e.originalType,s=e.parentName,u=i(e,["components","mdxType","originalType","parentName"]),d=p(r),m=n,g=d["".concat(s,".").concat(m)]||d[m]||c[m]||o;return r?a.createElement(g,l(l({ref:t},u),{},{components:r})):a.createElement(g,l({ref:t},u))}));function m(e,t){var r=arguments,n=t&&t.mdxType;if("string"==typeof e||n){var o=r.length,l=new Array(o);l[0]=d;var i={};for(var s in t)hasOwnProperty.call(t,s)&&(i[s]=t[s]);i.originalType=e,i.mdxType="string"==typeof e?e:n,l[1]=i;for(var p=2;p<o;p++)l[p]=r[p];return a.createElement.apply(null,l)}return a.createElement.apply(null,r)}d.displayName="MDXCreateElement"},7678:(e,t,r)=>{r.r(t),r.d(t,{assets:()=>s,contentTitle:()=>l,default:()=>c,frontMatter:()=>o,metadata:()=>i,toc:()=>p});var a=r(7462),n=(r(7294),r(3905));const o={},l="EEPROM Usage",i={unversionedId:"EEPROM Usage/index",id:"EEPROM Usage/index",title:"EEPROM Usage",description:"\ud83d\udcc3 Description",source:"@site/docs/EEPROM Usage/index.md",sourceDirName:"EEPROM Usage",slug:"/EEPROM Usage/",permalink:"/Microclimate-Recorder/docs/EEPROM Usage/",draft:!1,editUrl:"https://github.com/facebook/docusaurus/tree/main/packages/create-docusaurus/templates/shared/docs/EEPROM Usage/index.md",tags:[],version:"current",frontMatter:{},sidebar:"tutorialSidebar",next:{title:"Error Codes",permalink:"/Microclimate-Recorder/docs/Error Codes/"}},s={},p=[{value:"\ud83d\udcc3 Description",id:"-description",level:2},{value:"Usage Table",id:"usage-table",level:2},{value:"Backup log format",id:"backup-log-format",level:3}],u={toc:p};function c(e){let{components:t,...r}=e;return(0,n.kt)("wrapper",(0,a.Z)({},u,r,{components:t,mdxType:"MDXLayout"}),(0,n.kt)("h1",{id:"eeprom-usage"},"EEPROM Usage"),(0,n.kt)("h2",{id:"-description"},"\ud83d\udcc3 Description"),(0,n.kt)("p",null,"The EEPROM is a small data storage sector of the Arduino Nano Every (The board\nintended to be used for this project) that will be used to hold data that\nshouldn't be saved to the SD card at the time, and instead be saved to the\nboard itself. This table defines how that data should be saved and written."),(0,n.kt)("h2",{id:"usage-table"},"Usage Table"),(0,n.kt)("table",null,(0,n.kt)("thead",{parentName:"table"},(0,n.kt)("tr",{parentName:"thead"},(0,n.kt)("th",{parentName:"tr",align:null},"Byte Position"),(0,n.kt)("th",{parentName:"tr",align:null},"Storage Description"))),(0,n.kt)("tbody",{parentName:"table"},(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"0 to 24"),(0,n.kt)("td",{parentName:"tr",align:null},"System Name (Stored for convenience purposes and to ensure the SD card has the right name linked to the right account, which is more useful for multi-system setups)")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"25 to X"),(0,n.kt)("td",{parentName:"tr",align:null},"Other persistent parameters")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"X+1 to 256"),(0,n.kt)("td",{parentName:"tr",align:null},"Various backup logs each stored in the ",(0,n.kt)("a",{parentName:"td",href:"#%E2%9D%97-backup-log-format"},"following backup log format"))))),(0,n.kt)("h3",{id:"backup-log-format"},"Backup log format"),(0,n.kt)("p",null,"(Each log currently takes up ",(0,n.kt)("strong",{parentName:"p"},"32 bytes"),")"),(0,n.kt)("table",null,(0,n.kt)("thead",{parentName:"table"},(0,n.kt)("tr",{parentName:"thead"},(0,n.kt)("th",{parentName:"tr",align:null},"Byte Size"),(0,n.kt)("th",{parentName:"tr",align:null},"Storage Description"))),(0,n.kt)("tbody",{parentName:"table"},(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"20 Bytes"),(0,n.kt)("td",{parentName:"tr",align:null},"Date and time recorded")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"4 Bytes"),(0,n.kt)("td",{parentName:"tr",align:null},"Temperature (float)")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"4 Bytes"),(0,n.kt)("td",{parentName:"tr",align:null},"Humidity (float)")),(0,n.kt)("tr",{parentName:"tbody"},(0,n.kt)("td",{parentName:"tr",align:null},"4 Bytes"),(0,n.kt)("td",{parentName:"tr",align:null},"Pressure (float)")))))}c.isMDXComponent=!0}}]);