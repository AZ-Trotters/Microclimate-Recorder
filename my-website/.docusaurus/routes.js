import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/Microclimate-Recorder/blog',
    component: ComponentCreator('/Microclimate-Recorder/blog', 'ec6'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/archive',
    component: ComponentCreator('/Microclimate-Recorder/blog/archive', '044'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/first-blog-post',
    component: ComponentCreator('/Microclimate-Recorder/blog/first-blog-post', 'bf9'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/long-blog-post',
    component: ComponentCreator('/Microclimate-Recorder/blog/long-blog-post', '670'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/mdx-blog-post',
    component: ComponentCreator('/Microclimate-Recorder/blog/mdx-blog-post', '1d8'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/tags',
    component: ComponentCreator('/Microclimate-Recorder/blog/tags', '91c'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/tags/docusaurus',
    component: ComponentCreator('/Microclimate-Recorder/blog/tags/docusaurus', '553'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/tags/facebook',
    component: ComponentCreator('/Microclimate-Recorder/blog/tags/facebook', '4d1'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/tags/hello',
    component: ComponentCreator('/Microclimate-Recorder/blog/tags/hello', '88c'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/tags/hola',
    component: ComponentCreator('/Microclimate-Recorder/blog/tags/hola', 'b5c'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/blog/welcome',
    component: ComponentCreator('/Microclimate-Recorder/blog/welcome', 'c70'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/markdown-page',
    component: ComponentCreator('/Microclimate-Recorder/markdown-page', 'eed'),
    exact: true
  },
  {
    path: '/Microclimate-Recorder/docs',
    component: ComponentCreator('/Microclimate-Recorder/docs', '3b8'),
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
        path: '/Microclimate-Recorder/docs/intro',
        component: ComponentCreator('/Microclimate-Recorder/docs/intro', '6df'),
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
    component: ComponentCreator('/Microclimate-Recorder/', 'd2f'),
    exact: true
  },
  {
    path: '*',
    component: ComponentCreator('*'),
  },
];
