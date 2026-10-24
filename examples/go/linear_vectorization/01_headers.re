//go:generate re2go $INPUT -o $OUTPUT -i --api simple --vectorize-linear
package main

const (
	hdrOther = iota
	hdrContentLength
	hdrContentType
	hdrTransferEncoding
	hdrConnection
	hdrError
)

// Classify the name of an HTTP header line. Header names are long literals that are
// usually matched to the end, so most of their characters are compared eight at a time.
// The input must contain a colon or a non-name byte (for example CR) that ends
// the name. Empty strings and strings containing only name bytes are not valid
// inputs: YYFILL is disabled, and scalar reads require this terminator even
// though linear vectorization checks the remaining input length.
func header(yyinput string) int {
	yycursor, yymarker := 0, 0
	_ = yymarker

	/*!re2c
	re2c:yyfill:enable = 0;
	re2c:YYCTYPE = byte;

	"Content-Length:"    { return hdrContentLength }
	"Content-Type:"      { return hdrContentType }
	"Transfer-Encoding:" { return hdrTransferEncoding }
	"Connection:"        { return hdrConnection }
	[a-zA-Z-]+ ":"       { return hdrOther }
	*                    { return hdrError }
	*/
}

func main() {
	assert_eq := func(x, y int) { if x != y { panic("error") } }
	assert_eq(header("Content-Length: 42\r\n"), hdrContentLength)
	assert_eq(header("Content-Type: text/plain\r\n"), hdrContentType)
	assert_eq(header("Transfer-Encoding: chunked\r\n"), hdrTransferEncoding)
	assert_eq(header("Connection: close\r\n"), hdrConnection)
	assert_eq(header("Content-Language: en\r\n"), hdrOther)
	assert_eq(header("Connection-Id: 7\r\n"), hdrOther)
	assert_eq(header("Content\r\n"), hdrError)
	assert_eq(header("\r\n"), hdrError)
}
