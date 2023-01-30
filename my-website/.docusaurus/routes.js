import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/Microclimate-Recorder/__docusaurus/debug',
    component: ComponentCreator('/Microclimate-Recorder/__docusaurus/debug', 'af2'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/__docusaurus/debug/config',
    component: ComponentCreator('/Microclimate-Recorder/__docusaurus/debug/config', '4ae'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/__docusaurus/debug/content',
    component: ComponentCreator('/Microclimate-Recorder/__docusaurus/debug/content', 'a14'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/__docusaurus/debug/globalData',
    component: ComponentCreator('/Microclimate-Recorder/__docusaurus/debug/globalData', 'f05'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/__docusaurus/debug/metadata',
    component: ComponentCreator('/Microclimate-Recorder/__docusaurus/debug/metadata', 'ad5'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/__docusaurus/debug/registry',
    component: ComponentCreator('/Microclimate-Recorder/__docusaurus/debug/registry', '1b1'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/__docusaurus/debug/routes',
    component: ComponentCreator('/Microclimate-Recorder/__docusaurus/debug/routes', 'c02'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/markdown-page',
    component: ComponentCreator('/Microclimate-Recorder/markdown-page', 'eed'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/docs',
    component: ComponentCreator('/Microclimate-Recorder/docs', 'f99'),
    routes: [
      {
        path: '/Microclimate-Recorder/docs/Development/EEPROM Usage',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/EEPROM Usage', '45f'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Development/SD Card/statInfo',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/SD Card/statInfo', '0f9'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Development/SD Card/statInfo/batvolt.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/SD Card/statInfo/batvolt.txt', 'a0d'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Development/SD Card/statInfo/errorlog.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/SD Card/statInfo/errorlog.txt', '8cb'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Development/SD Card/statOpts',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/SD Card/statOpts', '7cd'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Development/SD Card/statOpts/statName.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/SD Card/statOpts/statName.txt', '2ed'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Development/SD Card/statOpts/time.txt',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/SD Card/statOpts/time.txt', '3b6'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Development/Task List',
        component: ComponentCreator('/Microclimate-Recorder/docs/Development/Task List', '02c'),
        exact: true,
        sidebar: "developmentSidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/DIY/Build Dependencies',
        component: ComponentCreator('/Microclimate-Recorder/docs/DIY/Build Dependencies', '318'),
        exact: true,
        sidebar: "diySidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/DIY/Supported Platforms',
        component: ComponentCreator('/Microclimate-Recorder/docs/DIY/Supported Platforms', 'e71'),
        exact: true,
        sidebar: "diySidebar"
      },
      {
        path: '/Microclimate-Recorder/docs/Error Codes',
        component: ComponentCreator('/Microclimate-Recorder/docs/Error Codes', 'b9a'),
        exact: true
      }
    ]
  },
  {
    path: '/Microclimate-Recorder/',
    component: ComponentCreator('/Microclimate-Recorder/', 'd2f'),
    exact: true
  },
  {
    path: '*',
    component: ComponentCreator('*'),
  },
];
