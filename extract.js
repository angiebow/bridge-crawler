const puppeteer = require("puppeteer");

(async () => {
  const url = process.argv[2]; 

  if (!url) {
    console.error("❌ No URL provided");
    process.exit(1);
  }

  const browser = await puppeteer.launch({ headless: true });
  const page = await browser.newPage();

  try {
    await page.goto(url, { waitUntil: "domcontentloaded" });

    const data = await page.evaluate(() => {
      return {
        title: document.title,
        links: Array.from(document.querySelectorAll("a")).map((a) => a.href),
      };
    });

    console.log(JSON.stringify(data, null, 2)); 
  } catch (err) {
    console.error("⚠️ Error fetching page:", err.message);
  } finally {
    await browser.close();
  }
})();
