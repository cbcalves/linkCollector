#include "request.h"

#include <curl/curl.h>
#include <spdlog/spdlog.h>

int writer(char* data, size_t size, size_t nmemb, std::string* writerData) {
    if (writerData == NULL)
        return 0;

    writerData->append(data, size * nmemb);

    return size * nmemb;
}

bool init(CURL*& conn, char* errorBuffer, std::string const& url, std::string* buffer) {
    CURLcode code;

    conn = curl_easy_init();

    if (conn == NULL) {
        spdlog::critical("{} Failed to create CURL connection", __PRETTY_FUNCTION__);
        exit(EXIT_FAILURE);
    }

    code = curl_easy_setopt(conn, CURLOPT_ERRORBUFFER, errorBuffer);
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set error buffer [{}]", __PRETTY_FUNCTION__, static_cast<int>(code));
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_URL, url.c_str());
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set URL [{}]", __PRETTY_FUNCTION__, errorBuffer);
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_FOLLOWLOCATION, 1L);
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set redirect option [{}]", __PRETTY_FUNCTION__, errorBuffer);
        return false;
    }

#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who is not using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    code = curl_easy_setopt(conn, CURLOPT_SSL_VERIFYPEER, 0L);
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set skip verify peer [{}]", __PRETTY_FUNCTION__, errorBuffer);
        return false;
    }
#endif

#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you are connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    code = curl_easy_setopt(conn, CURLOPT_SSL_VERIFYHOST, 0L);
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set skip verify host [{}]", __PRETTY_FUNCTION__, errorBuffer);
        return false;
    }
#endif

    /* cache the CA cert bundle in memory for a week */
    code = curl_easy_setopt(conn, CURLOPT_CA_CACHE_TIMEOUT, 604800L);
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set certificates [{}]", __PRETTY_FUNCTION__, errorBuffer);
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEFUNCTION, writer);
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set writer [{}]", __PRETTY_FUNCTION__, errorBuffer);
        return false;
    }

    code = curl_easy_setopt(conn, CURLOPT_WRITEDATA, buffer);
    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set write data [{}]", __PRETTY_FUNCTION__, errorBuffer);
        return false;
    }

    return true;
}

namespace request {

std::optional<std::string> request(std::string const& url) {
    std::string buffer{};
    char errorBuffer[CURL_ERROR_SIZE]{};
    CURL* conn{NULL};
    CURLcode code;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Initialize CURL connection
    if (!init(conn, errorBuffer, url, &buffer)) {
        spdlog::critical("{} Connection initialization failed", __PRETTY_FUNCTION__);
        return {};
    }

    // Retrieve content for the URL
    code = curl_easy_perform(conn);
    curl_easy_cleanup(conn);

    if (code != CURLE_OK) {
        spdlog::critical("{} Failed to set get '{}'", __PRETTY_FUNCTION__, url);
        return {};
    }

    return buffer;
}

}
