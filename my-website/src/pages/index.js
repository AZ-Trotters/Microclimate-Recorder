import React from 'react';
import clsx from 'clsx';
import Link from '@docusaurus/Link';
import useDocusaurusContext from '@docusaurus/useDocusaurusContext';
import Layout from '@theme/Layout';
import HomepageFeatures from '@site/src/components/HomepageFeatures';

import styles from './index.module.css';

function HomepageHeader() {
  const {siteConfig} = useDocusaurusContext();
  return (
    // <header className={clsx('hero hero--primary', styles.header)}>
      <div className="container">
        <br></br>
        {/* <h1>{siteConfig.title}</h1> */}
        <br></br>
        <div align="center">
          <h1>Welcome!</h1>
        </div>
          <a href = "https://az-trotters.github.io/Microclimate-Recorder/docs/DIY/Build%20Dependencies"><h3>Looking to build your own?</h3></a> 
          <a href = "https://az-trotters.github.io/Microclimate-Recorder/docs/Error%20Codes"><h3>Have an error code?</h3></a> 
          <a href = "https://az-trotters.github.io/Microclimate-Recorder/docs/Development/EEPROM%20Usage"><h3>Want to develop custom code? Get a description of how this project works here.</h3></a> 
          <a href = "https://az-trotters.github.io/Microclimate-Recorder/docs/FAQ"><h3>Have another question?</h3></a> 
      </div>
    // </header>
  );
}


export default function Home() {
  const {siteConfig} = useDocusaurusContext();
  return (
    <Layout
      title={`Hello from ${siteConfig.title}`}
      description="Description will go into a meta tag in <head />">
      <HomepageHeader />
      {/* <main>
        <HomepageFeatures />
      </main> */}
    </Layout>
  );
}
