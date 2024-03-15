package de.gnd.testcTester;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class MyStatusTypeTest {

    @Test
    void getReasonPhraseReturnsExpectedReasonPhraseForBadRequest() {
        // Given
        MyStatusType statusType = MyStatusType.BAD_REQUEST;

        // When
        String reasonPhrase = statusType.getReasonPhrase();

        // Then
        assertEquals("PASSWORD_EXISTS", reasonPhrase);
    }
}
