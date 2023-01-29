import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/Microclimate-Recorder/markdown-page',
    component: ComponentCreator('/Microclimate-Recorder/markdown-page', 'cc7'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/docs',
    component: ComponentCreator('/Microclimate-Recorder/docs', '56f'),
    routes: [
      {
        path: '/Microclimate-Recorder/docs/EEPROM Usage',
        component: ComponentCreator('/Microclimate-Recorder/docs/EEPROM Usage', '44c'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Error Codes',
        component: ComponentCreator('/Microclimate-Recorder/docs/Error Codes', '1a5'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Intro',
        component: ComponentCreator('/Microclimate-Recorder/docs/Intro', '332'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/SD Card/statInfo',
        component: ComponentCreator('/Microclimate-Recorder/docs/SD Card/statInfo', '923'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/SD Card/statInfo/batvolt.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/SD Card/statInfo/batvolt.txt', '352'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/SD Card/statInfo/errorlog.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/SD Card/statInfo/errorlog.txt', 'd1f'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/SD Card/statInfo/wthrvals.csv',
        component: ComponentCreator('/Microclimate-Recorder/docs/SD Card/statInfo/wthrvals.csv', '0a6'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/SD Card/statOpts',
        component: ComponentCreator('/Microclimate-Recorder/docs/SD Card/statOpts', '939'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/SD Card/statOpts/statName.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/SD Card/statOpts/statName.txt', '4f6'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/SD Card/statOpts/time.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/SD Card/statOpts/time.txt', '302'),
        exact: true,
        sidebar: "tutorialSidebar"
      }
    ]
  },
  {
    path: '/Microclimate-Recorder/',
    component: ComponentCreator('/Microclimate-Recorder/', 'bf9'),
    exact: true
  },
  {
    path: '*',
    component: ComponentCreator('*'),
  },
];
