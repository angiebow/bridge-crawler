# 🕸️ BridgeCrawler

BridgeCrawler is a simple prototype that demonstrates how C++ can integrate with browser automation tools like Puppeteer.  
It acts as a **bridge**: C++ takes user input, Puppeteer crawls the page, and results are sent back to C++ for display.

## Features
- C++ CLI program that accepts a website URL.
- Puppeteer script (Node.js) that opens the site headlessly.
- Extracts and returns:
  - Page Title
  - All Links on the page
- JSON-based communication between Puppeteer and C++.