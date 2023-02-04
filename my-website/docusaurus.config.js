// @ts-check
// Note: type annotations allow type checking and IDEs autocompletion

const lightCodeTheme = require('prism-react-renderer/themes/github');
const darkCodeTheme = require('prism-react-renderer/themes/dracula');

/** @type {import('@docusaurus/types').Config} */
const config = {
  title: 'Microclimate Recorder',
  favicon: 'img/favicon.ico',

  // Set the production url of your site here
  url: 'https://az-trotters.github.io',
  // Set the /<baseUrl>/ pathname under which your site is served
  // For GitHub pages deployment, it is often '/<projectName>/'
  baseUrl: '/Microclimate-Recorder/',

  // GitHub pages deployment config.
  // If you aren't using GitHub pages, you don't need these.
  organizationName: 'AZ-Trotters', // Usually your GitHub org/user name.
  projectName: 'Microclimate-Recorder', // Usually your repo name.
  deploymentBranch: 'gh-pages',
  trailingSlash: false,

  onBrokenLinks: 'throw',
  onBrokenMarkdownLinks: 'warn',

  // Even if you don't use internalization, you can use this field to set useful
  // metadata like html lang. For example, if your site is Chinese, you may want
  // to replace "en" with "zh-Hans".
  i18n: {
    defaultLocale: 'en',
    locales: ['en'],
  },

  presets: [
    [
      'classic',
      /** @type {import('@docusaurus/preset-classic').Options} */
      ({
        docs: {
          sidebarPath: require.resolve('./sidebars.js'),
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/AZ-Trotters/Microclimate-Recorder/blob/site-source/my-website',
        },
        blog: {
          showReadingTime: true,
          // Please change this to your repo.
          // Remove this to remove the "edit this page" links.
          editUrl:
            'https://github.com/facebook/docusaurus/tree/main/packages/create-docusaurus/templates/shared/',
        },
        theme: {
          customCss: require.resolve('./src/css/custom.css'),
        },
      }),
    ],
  ],

  themeConfig:
    /** @type {import('@docusaurus/preset-classic').ThemeConfig} */
    ({
      // Replace with your project's social card
      image: 'img/docusaurus-social-card.jpg',
      navbar: {
        title: 'Microclimate Recorder',
        logo: {
          alt: 'My Site Logo',
          src: 'img/logo.svg',
        },
        items: [
          // {
          //   type: 'dropdown',
          //   docId: 'intro',
          //   position: 'left',
          //   label: 'Docs',
          //   items: [
          //     {
          //       type: 'doc',
          //       label: 'Error Codes',
          //       docId: 'Error Codes/index'
          //     },
          //     {
          //       type: 'doc',
          //       label: 'Development',
          //       docId: 'Development/EEPROM Usage/index'
          //     }
          //   ]
          // },
          {
            type: 'doc',
            docId: 'Error Codes/index',
            position: 'left',
            label: 'Error Codes',
          },
          {
            type: 'doc',
            docId: 'DIY/Build Dependencies/index',
            position: 'left',
            label: 'DIY',
          },
          {
            type: 'doc',
            docId: 'Development/EEPROM Usage/index',
            position: 'left',
            label: 'Development',
          },
          {
            type: 'doc',
            docId: 'FAQ/index',
            position: 'left',
            label: 'FAQ',
          },
          // {
          //   type: 'doc',
          //   docId: 'devguide/intro',
          //   position: 'left',
          //   label: 'Dev Guide',
          // },
          // {to: 'devguide/Intro', label: 'Dev Guide', position: 'left'},
          // {
          //   type: 'localeDropdown',
          //   position: 'right',
          // },
          {
            href: 'https://github.com/AZ-Trotters/Microclimate-Recorder',
            label: 'GitHub',
            position: 'right',
          },
        ],
      },
      footer: {
        style: 'dark',
        links: [
          {
            title: 'Community',
            items: [
              {
                label: 'GitHub Repository',
                href: 'https://github.com/AZ-Trotters/Microclimate-Recorder',
              },
              {
                label: 'GitHub Organization',
                href: 'https://github.com/AZ-Trotters',
              },
            ],
          },
        ],
        copyright: `Copyright © ${new Date().getFullYear()} AZ-Trotters Built with Docusaurus.`,
      },
      prism: {
        theme: lightCodeTheme,
        darkTheme: darkCodeTheme,
      },
    }),
};

module.exports = config;