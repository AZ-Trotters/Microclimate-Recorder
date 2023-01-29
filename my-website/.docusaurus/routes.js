import React from 'react';
import ComponentCreator from '@docusaurus/ComponentCreator';

export default [
  {
    path: '/blog',
    component: ComponentCreator('/blog', '2e8'),
    exact: true
  },
  {
    path: '/blog/archive',
    component: ComponentCreator('/blog/archive', '329'),
    exact: true
  },
  {
    path: '/blog/first-blog-post',
    component: ComponentCreator('/blog/first-blog-post', 'd3c'),
    exact: true
  },
  {
    path: '/blog/long-blog-post',
    component: ComponentCreator('/blog/long-blog-post', '35a'),
    exact: true
  },
  {
    path: '/blog/mdx-blog-post',
    component: ComponentCreator('/blog/mdx-blog-post', '519'),
    exact: true
  },
  {
    path: '/blog/tags',
    component: ComponentCreator('/blog/tags', 'e5f'),
    exact: true
  },
  {
    path: '/blog/tags/docusaurus',
    component: ComponentCreator('/blog/tags/docusaurus', '263'),
    exact: true
  },
  {
    path: '/blog/tags/facebook',
    component: ComponentCreator('/blog/tags/facebook', 'c8b'),
    exact: true
  },
  {
    path: '/blog/tags/hello',
    component: ComponentCreator('/blog/tags/hello', '076'),
    exact: true
  },
  {
    path: '/blog/tags/hola',
    component: ComponentCreator('/blog/tags/hola', 'bf0'),
    exact: true
  },
  {
    path: '/blog/welcome',
    component: ComponentCreator('/blog/welcome', '220'),
    exact: true
  },
  {
    path: '/markdown-page',
    component: ComponentCreator('/markdown-page', '100'),
    exact: true
  },
  {
    path: '/docs',
    component: ComponentCreator('/docs', '6ca'),
    routes: [
      {
        path: '/docs/EEPROM Usage/',
        component: ComponentCreator('/docs/EEPROM Usage/', 'f92'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/Error Codes/',
        component: ComponentCreator('/docs/Error Codes/', 'c35'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/intro',
        component: ComponentCreator('/docs/intro', 'aed'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/SD Card/statInfo/',
        component: ComponentCreator('/docs/SD Card/statInfo/', 'e35'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/SD Card/statInfo/batvolt.txt/',
        component: ComponentCreator('/docs/SD Card/statInfo/batvolt.txt/', '700'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/SD Card/statInfo/errorlog.txt/',
        component: ComponentCreator('/docs/SD Card/statInfo/errorlog.txt/', '7e3'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/SD Card/statOpts/',
        component: ComponentCreator('/docs/SD Card/statOpts/', 'a32'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/SD Card/statOpts/statName.txt/',
        component: ComponentCreator('/docs/SD Card/statOpts/statName.txt/', '41d'),
        exact: true,
        sidebar: "tutorialSidebar"
      },
      {
        path: '/docs/SD Card/statOpts/time.txt/',
        component: ComponentCreator('/docs/SD Card/statOpts/time.txt/', 'bcd'),
        exact: true,
        sidebar: "tutorialSidebar"
      }
    ]
  },
  {
    path: '/',
    component: ComponentCreator('/', 'cc9'),
    exact: true
  },
  {
    path: '*',
    component: ComponentCreator('*'),
  },
];
