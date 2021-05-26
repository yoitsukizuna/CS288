#import mysql.connector
import pymysql.cursors
import xml.dom.minidom
import sys
import re

#dom parse and get product information

def domparse():
    doc = xml.dom.minidom.parse(sys.argv[1])

    price=float(0)
    rate=float(0)
    site=""
    name=""
    description=""
    url=""
    img=""

    #got general informations
    namelist=doc.getElementsByTagName("meta")
    len=namelist.length
    for n in range(len):
        x = namelist[n].attributes
        if x.getNamedItem("property") is not None:
            if x.getNamedItem("property").nodeValue=="og:site_name":
                site = x.getNamedItem("content").nodeValue
    for n in range(len):
        x = namelist[n].attributes
        if x.getNamedItem("property") is not None:
            if x.getNamedItem("property").nodeValue == "og:description":
                description =x.getNamedItem("content").nodeValue
            if x.getNamedItem("property").nodeValue == "og:image":
                img=x.getNamedItem("content").nodeValue
            if x.getNamedItem("property").nodeValue == "og:url":
                url=x.getNamedItem("content").nodeValue
            if x.getNamedItem("property").nodeValue == "og:title":
                namel = x.getNamedItem("content").nodeValue.split("-")
                for n in namel:
                    sitea=" "+site
                    if n!=site and n!=sitea:
                        name+=n

    #for rating in best buy
    span =doc.getElementsByTagName("span")
    lens=span.length
    for m in range(lens):
        y=span[m].attributes
        if y.getNamedItem("class") is not None:
            if y.getNamedItem("class").nodeValue=="price" and price ==0.00:
                ps = span[m].firstChild.nodeValue
                price=float(ps[1:])
            if y.getNamedItem("class").nodeValue=="ugc-c-review-average" and rate==0.00:
                rate=float(span[m].firstChild.nodeValue)
    
    #for price in micro center
    mic =doc.getElementsByTagName("div")
    lent=mic.length
    for p in range(lent):
        z=mic[p].attributes
        if z.getNamedItem("class") is not None:
            if z.getNamedItem("class").nodeValue=="savings" and price==0.00:
                if mic[p].childNodes[0]!='None':
                    if mic[p].childNodes[0].firstChild is not None:
                        ps=mic[p].childNodes[0].firstChild.nodeValue
                        price=float(ps[1:])
            if z.getNamedItem("class").nodeValue=="pricing-price__regular-price" and price==0.00:#for price in best buy
                if mic[p].childNodes[0]!='None':
                    ps=mic[p].childNodes[0].nodeValue.split("$")
                    price=float(ps[1])
            if z.getNamedItem("class").nodeValue=="priceView-hero-price priceView-customer-price" and price==0.00:
                if mic[p].childNodes[0]!='None':
                    ps=mic[p].childNodes[0].firstChild.nodeValue.split("$")
                    price=float(ps[1])

#for ratings in micro center
    sc = doc.getElementsByTagName("script")
    lensc =sc.length
    for q in range(lensc):
        if sc[q].childNodes.length>0:
            if sc[q].childNodes[0].nodeValue is not None:
                w=sc[q].childNodes[0].nodeValue
                ww=re.search("ratingValue\": \"[0-9\.]+\"",w)#for rating in micro center
                if ww != None and rate==0.00:
                    www=ww.group(0) # got ratingValue": "4.775400" 
                    rate = float(www.split("\"")[2])
                else:
                    ww=re.search("rating\\\":[0-9\.]+",w)#in best buy, rating\":4.48
                    if ww!=None and rate ==0.00:
                        www=ww.group(0)
                        rate= float(www.split(":")[1])

                pp=re.search("price\\\":[0-9\.]+",w)#for price in best buy 2
                if pp !=None and price ==0.00:
                    ppp=pp.group(0) #got price\":899.99
                    price= float(ppp.split(":")[1])
                else:
                    pp=re.search("productPrice\':\'[0-9\.]+",w)#for price in micro center 
                    if pp!=None and  price==0.00:
                        ppp=pp.group(0) #got productPrice':'169.99
                        price = float(ppp.split("\'")[2])

    product ={"Product Name": name, "Description": description, "Price": price, "Product URL": url, "Image": img, "Review": rate,"site": site}
    return product


##################



def insert(cursor,a):
    query = 'INSERT INTO product(product_name,description,price,product_url,image,review,site) VALUES (%s,%s,%s,%s,%s,%s,%s)'
    cursor.execute(query, (a.get("Product Name"),a.get("Description"),a.get("Price"), a.get("Product URL"),a.get("Image"),a.get("Review"),a.get("site")))


def update(cursor,a):
    query = 'UPDATE product SET price=%s WHERE product_url=%s'
    cursor.execute(query, (a.get("Price"),a.get("Product URL")))


try:
    #cnx = mysql.connector.connect(host='localhost', user='zhaoshu', password='zhaoshu', database='demo')
    cnx = pymysql.connect(host='localhost', user='zhaoshu', password='zhaoshu', database='demo')
    cursor = cnx.cursor()
    a=domparse()  #get the product info and pass into cursor
    if int(sys.argv[2])>1:# if it is the second time download, use update
        print("update!")
        update(cursor,a)
        cnx.commit()
    else :
        print("insert")
        insert(cursor,a)
        cnx.commit()
    
    cursor.close()
#except mysql.connector.Error as err:
except pymysql.Error as err:
    print(err)
finally:
    try:
        cnx
    except NameError:
        pass
    else:
        cnx.close()
    