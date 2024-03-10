# Start the tests via `make test-debug` or `make test-release`


async def test_start(service_client):
    response = await service_client.post('v1/start',
                                         params={'name': 'Test Name'}, )
    assert response.status == 200
    assert len(response.text) == 32


async def test_check(service_client):
    token_response = await service_client.post('v1/start',
                                               params={'name': 'Test Name'}, )

    response = await service_client.post(
        '/v1/check',
        params={'token': token_response.text, 'word': 'apple'},
    )
    assert response.status == 200


async def test_check_unreal_token(service_client):
    token_response = await service_client.post('v1/start',
                                               params={'name': 'Test Name'}, )

    response = await service_client.post(
        '/v1/check',
        params={'token': "unreal_token", 'word': 'apple'},
    )
    assert response.status == 400


async def test_check_unreal_word(service_client):
    token_response = await service_client.post('v1/start',
                                               params={'name': 'Test Name'}, )

    response = await service_client.post(
        '/v1/check',
        params={'token': token_response.text, 'word': 'unreal'},
    )
    assert response.status == 400


async def test_check_no_token(service_client):
    token_response = await service_client.post('v1/start',
                                               params={'name': 'Test Name'}, )

    response = await service_client.post(
        '/v1/check',
        params={'word': 'unreal'},
    )
    assert response.status == 400


async def test_check_no_word(service_client):
    token_response = await service_client.post('v1/start',
                                               params={'name': 'Test Name'}, )

    response = await service_client.post(
        '/v1/check',
        params={'token': token_response.text},
    )
    assert response.status == 400
