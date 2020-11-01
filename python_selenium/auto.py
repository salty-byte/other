from msedge.selenium_tools import Edge, EdgeOptions

options = EdgeOptions()
options.use_chromium = True
# options.add_argument("headless")
driver = Edge(options = options)

driver.get('https://google.com/')
driver.quit()
