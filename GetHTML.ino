void getHTML(EthernetClient cl)
{
    cl.println("HTTP/1.1 200 OK");
    cl.println("Content-Type: text/html");
    cl.println();
    cl.println(names);
}
